/*
 * Copyright (C) 2015 The CyanogenMod Project
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

#define CAMERA_PARAMETERS_EXTRA_C \
const char CameraParameters::KEY_CONTINUOUS_BURST_NUM[] = "continuous-burst-num"; \
const char CameraParameters::KEY_CONTINUOUS_BURST_FPS[] = "continuous-burst-fps"; \
const char CameraParameters::ASUS_SUPER_RESOLUTION[] = "asus_super_resolution"; \
const char CameraParameters::ASUS_CAMERA_MODE[] = "asus_camera_mode"; \
const char CameraParameters::ASUS_DETECT_LIGHT[] = "asus_detect_light"; \
const char CameraParameters::ASUS_IMAGE_OPTIMIZE[] = "asus_image_optimize"; \
const char CameraParameters::ASUS_VIDEO_OPTIMIZE[] = "asus_video_optimize"; \
const char CameraParameters::ASUS_VIDEO_LOWLIGHT[] = "asus_video_lowlight"; \
const char CameraParameters::ASUS_VIDEO_LOWLIGHT_INTENSITY[] = "asus_video_lowlight_intensity"; \
const char CameraParameters::ASUS_VIDEO_LOWLIGHT_DENOISE[] = "asus_video_lowlight_denoise"; \
const char CameraParameters::ASUS_VIDEO_LOWLIGHT_CONTRAST[] = "asus_video_lowlight_contrast"; \
const char CameraParameters::ASUS_VIDEO_LOWLIGHT_AUTOCONTRAST[] = "asus_video_lowlight_autocontrast"; \
const char CameraParameters::ASUS_VIDEO_LOWLIGHT_NEED_DENOISE[] = "asus_video_lowlight_need_denoise"; \
const char CameraParameters::ASUS_TIMESHIFT_MODE[] = "asus_timeshift_mode"; \
const char CameraParameters::ASUS_METERING_MODE[] = "asus_metering_mode"; \
const char CameraParameters::ASUS_COLOR_TEMPERATURE[] = "asus_color_temperature"; \
const char CameraParameters::ASUS_MANUAL_FOCUS[] = "asus_manual_focus"; \
const char CameraParameters::ASUS_SET_SHUTTER_SPEED[] = "asus_set_shutter_speed"; \
const char CameraParameters::ASUS_SET_NOISE_REDUCTION[] = "asus_set_noise_reduction"; \
const char CameraParameters::ASUS_WDR_INTENSITY[] = "asus_wdr_intensity"; \
const char CameraParameters::ASUS_REMOVE_YELLOW_TINT[] = "asus_remove_yellow_tint"; \
const char CameraParameters::ASUS_MANAUAL_CONTRAST[] = "asus_manmual_contrast"; \
const char CameraParameters::ASUS_MANAUAL_DETAIL_ENHANCE[] = "asus_manual_detail_enhance"; \
const char CameraParameters::ASUS_MANAUAL_SATURATION[] = "asus_manual_saturation"; \
const char CameraParameters::ASUS_MANAUAL_SHARPNESS[] = "asus_manual_sharpness"; \
const char CameraParameters::ASUS_SCENE_MODE[] = "asus_scene_mode"; \
const char CameraParameters::ASUS_XE_ISO[] = "asus_xe_iso"; \
const char CameraParameters::ASUS_XE_BRIGHTNESS[] = "asus_xe_brightness"; \
const char CameraParameters::ASUS_XE_EXPOSURE_TIME[] = "asus_xe_exposure_time"; \
const char CameraParameters::ASUS_ULTRA_PIXEL_MODE[] = "asus_ultra_pixel_mode"; \
const char CameraParameters::ASUS_EIS_MODE[] = "asus_eis_mode"; \
const char CameraParameters::ASUS_BEAUTY_MODE[] = "asus_beauty_mode"; \
const char CameraParameters::ASUS_3DNR_IS_APPLIED[] = "asus_3dnr_is_applied"; \
const char CameraParameters::ASUS_COLOR_TEMP_VALUES[] = "asus_color_temp_values"; \
const char CameraParameters::ASUS_FOCUS_RANGE_VALUES[] = "asus_focus_range_values"; \
const char CameraParameters::ASUS_SHUTTER_SPEED_VALUES[] = "asus_shutter_speed_values"; \
\
/* LAST_LINE OF CAMERA_PARAMETERS_EXTRA_C, every line before this one *MUST* have
 * a backslash \ at the end of the line or else everything will break.
 */

#define CAMERA_PARAMETERS_EXTRA_H \
    static const char KEY_CONTINUOUS_BURST_NUM[]; \
    static const char KEY_CONTINUOUS_BURST_FPS[]; \
    static const char ASUS_SUPER_RESOLUTION[]; \
    static const char ASUS_CAMERA_MODE[]; \
    static const char ASUS_DETECT_LIGHT[]; \
    static const char ASUS_IMAGE_OPTIMIZE[]; \
    static const char ASUS_VIDEO_OPTIMIZE[]; \
    static const char ASUS_VIDEO_LOWLIGHT[]; \
    static const char ASUS_VIDEO_LOWLIGHT_INTENSITY[]; \
    static const char ASUS_VIDEO_LOWLIGHT_DENOISE[]; \
    static const char ASUS_VIDEO_LOWLIGHT_CONTRAST[]; \
    static const char ASUS_VIDEO_LOWLIGHT_AUTOCONTRAST[]; \
    static const char ASUS_VIDEO_LOWLIGHT_NEED_DENOISE[]; \
    static const char ASUS_TIMESHIFT_MODE[]; \
    static const char ASUS_METERING_MODE[]; \
    static const char ASUS_COLOR_TEMPERATURE[]; \
    static const char ASUS_MANUAL_FOCUS[]; \
    static const char ASUS_SET_SHUTTER_SPEED[]; \
    static const char ASUS_SET_NOISE_REDUCTION[]; \
    static const char ASUS_WDR_INTENSITY[]; \
    static const char ASUS_REMOVE_YELLOW_TINT[]; \
    static const char ASUS_MANAUAL_CONTRAST[]; \
    static const char ASUS_MANAUAL_DETAIL_ENHANCE[]; \
    static const char ASUS_MANAUAL_SATURATION[]; \
    static const char ASUS_MANAUAL_SHARPNESS[]; \
    static const char ASUS_SCENE_MODE[]; \
    static const char ASUS_XE_ISO[]; \
    static const char ASUS_XE_BRIGHTNESS[]; \
    static const char ASUS_XE_EXPOSURE_TIME[]; \
    static const char ASUS_ULTRA_PIXEL_MODE[]; \
    static const char ASUS_EIS_MODE[]; \
    static const char ASUS_BEAUTY_MODE[]; \
    static const char ASUS_3DNR_IS_APPLIED[]; \
    static const char ASUS_COLOR_TEMP_VALUES[]; \
    static const char ASUS_FOCUS_RANGE_VALUES[]; \
    static const char ASUS_SHUTTER_SPEED_VALUES[]; \
    \
    /* LAST_LINE OF CAMERA_PARAMETERS_EXTRA_H, every line before this one *MUST* have
     * a backslash \ at the end of the line or else everything will break.
     */
