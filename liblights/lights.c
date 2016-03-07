/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "lights"
#include <cutils/log.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <hardware/hardware.h>
#include <hardware/lights.h>

/******************************************************************************/

#define MAX_PATH_SIZE 80

#define LED_LIGHT_OFF 0
#define LED_LIGHT_ON 255

enum {
    ATTENTION = 0,
    NOTIFICATION,
    BATTERY,
    LIGHT_MAX,
};

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static struct light_state_t g_lights[LIGHT_MAX];

char const*const LCD_FILE = "/sys/class/backlight/psb-bl/brightness";

char const*const GREEN_LED_FILE
        = "/sys/class/leds/green/brightness";

char const*const RED_LED_FILE
        = "/sys/class/leds/red/brightness";

char const*const GREEN_BLINK_FILE
        = "/sys/class/leds/green/blink";

char const*const RED_BLINK_FILE
        = "/sys/class/leds/red/blink";

/**
 * device methods
 */

void init_globals(void)
{
    // init the mutex
    pthread_mutex_init(&g_lock, NULL);
}

static int
write_str(char const* path, char const* str)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        ssize_t amt = write(fd, str, strlen(str));
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            ALOGE("write_int failed to open %s\n", path);
            already_warned = 1;
        }
        return -errno;
    }
}

static int
write_int(char const* path, int value)
{
    char buffer[20];
    sprintf(buffer, "%d\n", value);
    return write_str(path, buffer);
}

static int
write_blink(char const* path, int value, int on_ms, int off_ms)
{
    char buffer[100];

    sprintf(buffer, "%d %d %d\n", value, on_ms, off_ms);
    return write_str(path, buffer);
}

static int
is_lit(struct light_state_t const* state)
{
    return state->color & 0x00ffffff;
}

static int
set_light_backlight(__attribute__((unused)) struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    int brightness = (state->color & 0xff);
    if(!dev) {
        return -1;
    }
    pthread_mutex_lock(&g_lock);
    err = write_int(LCD_FILE, brightness);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int
set_light_locked(struct light_state_t const* state)
{
    int blink;
    int red = 0;
    int green = 0;
    int blue = 0;
    unsigned int colorRGB = state->color;

    switch (state->flashMode) {
        case LIGHT_FLASH_TIMED:
        case LIGHT_FLASH_HARDWARE:
            blink = 1;
            break;
        case LIGHT_FLASH_NONE:
        default:
            blink = 0;
            break;
    }

    red = ((colorRGB >> 16) & 0xFF);
    green = ((colorRGB >> 8) & 0xFF);
    blue = (colorRGB & 0xFF);

    if (blue)
        green = red = blue;

    ALOGD("set_light_locked colorRGB=%08X, red=%d, green=%d, blink=%d",
            colorRGB, red, green, blink);

    if (blink) {
        write_int(RED_LED_FILE, LED_LIGHT_OFF);
        write_int(GREEN_LED_FILE, LED_LIGHT_OFF);
        write_blink(RED_BLINK_FILE, (red ? 1 : 0), state->flashOnMS, state->flashOffMS);
        write_blink(GREEN_BLINK_FILE, (green ? 1 : 0), state->flashOnMS, state->flashOffMS);
    } else {
        write_int(RED_BLINK_FILE, blink);
        write_int(GREEN_BLINK_FILE, blink);
        write_int(RED_LED_FILE, LED_LIGHT_OFF);
        write_int(GREEN_LED_FILE, LED_LIGHT_OFF);
        write_int(RED_LED_FILE, red);
        write_int(GREEN_LED_FILE, green);
    }

    return 0;
}

static int
handle_led_prioritized_locked(struct light_state_t const* state)
{
    if (is_lit(&g_lights[ATTENTION])) {
        return set_light_locked(&g_lights[ATTENTION]);
    } else if (is_lit(&g_lights[NOTIFICATION])) {
        return set_light_locked(&g_lights[NOTIFICATION]);
    } else if (is_lit(&g_lights[BATTERY])) {
        return set_light_locked(&g_lights[BATTERY]);
    } else {
        return set_light_locked(state);
    }
}

static int
set_light_notifications(__attribute__((unused)) struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    pthread_mutex_lock(&g_lock);
    g_lights[NOTIFICATION] = *state;
    err = handle_led_prioritized_locked(state);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int
set_light_attention(__attribute__((unused)) struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    pthread_mutex_lock(&g_lock);
    g_lights[ATTENTION] = *state;
    err = handle_led_prioritized_locked(state);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int
set_light_battery(__attribute__((unused)) struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    pthread_mutex_lock(&g_lock);
    g_lights[BATTERY] = *state;
    err = handle_led_prioritized_locked(state);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int set_light_noop(__attribute__((unused)) struct light_device_t *dev,
            __attribute__((unused)) struct light_state_t const *state)
{
    return 0;
}

/** Close the lights device */
static int
close_lights(struct light_device_t *dev)
{
    if (dev) {
        free(dev);
    }
    return 0;
}


/******************************************************************************/

/**
 * module methods
 */

/** Open a new instance of a lights device using name */
static int open_lights(const struct hw_module_t* module, char const* name,
        struct hw_device_t** device)
{
    int (*set_light)(struct light_device_t* dev,
            struct light_state_t const* state);

    if (0 == strcmp(LIGHT_ID_BACKLIGHT, name))
        set_light = set_light_backlight;
    else if (0 == strcmp(LIGHT_ID_NOTIFICATIONS, name))
        set_light = set_light_notifications;
    else if (0 == strcmp(LIGHT_ID_ATTENTION, name))
        set_light = set_light_attention;
    else if (0 == strcmp(LIGHT_ID_BATTERY, name))
        set_light = set_light_battery;
    else if (0 == strcmp(LIGHT_ID_BUTTONS, name))
        set_light = set_light_noop;
    else
        return -EINVAL;

    pthread_once(&g_init, init_globals);

    struct light_device_t *dev = malloc(sizeof(struct light_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light = set_light;

    *device = (struct hw_device_t*)dev;
    return 0;
}

static struct hw_module_methods_t lights_module_methods = {
    .open =  open_lights,
};

/*
 * The lights Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "Zenfone2 Lights Module",
    .author = "The CyanogenMod Project",
    .methods = &lights_module_methods,
};
