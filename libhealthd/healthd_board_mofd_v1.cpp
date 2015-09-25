/*
 * Copyright (C) 2013 The Android Open Source Project
 * Copyright (C) 2013 The CyanogenMod Project
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

#include <healthd.h>

static int mapBatteryStatusString(const char *status)
{
    if (strcmp(status, "Quick charging") == 0)
        return android::BATTERY_STATUS_CHARGING;
    if (strcmp(status, "Not Quick charging") == 0)
        return android::BATTERY_STATUS_CHARGING;
    return HEALTHD_MAP_CONTINUE_SEARCH;
}

static int mapChargeTypeString(const char *charge_type)
{
    if (strcmp(charge_type, "Quick charging") == 0)
        return android::BATTERY_CHARGE_TYPE_FAST_CHARGING;
    else
        return android::BATTERY_CHARGE_TYPE_UNKNOWN;
}

void healthd_board_init(struct healthd_config *config)
{
    config->batteryChargeTypePath  = "/sys/class/power_supply/battery/status";
    config->mapBatteryStatusString = mapBatteryStatusString;
    config->mapChargeTypeString    = mapChargeTypeString;
}


int healthd_board_battery_update(__attribute__((unused)) struct android::BatteryProperties *props)
{
    // return 0 to log periodic polled battery status to kernel log
    return 0;
}
