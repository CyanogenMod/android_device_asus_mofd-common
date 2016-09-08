LOCAL_PATH := $(call my-dir)

# Audio

include $(CLEAR_VARS)

LOCAL_SRC_FILES := icu55.c
LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_icu
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

# Audio

include $(CLEAR_VARS)

LOCAL_SRC_FILES := icu55.c
LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_audio
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

# GPSD

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    icu55.c

LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_gps
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)

# MMGR

include $(CLEAR_VARS)

LOCAL_SRC_FILES := icu55.c
LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_mmgr
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

# sensors

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
     icu55.c

LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_sensors
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

# tcs

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
     icu55.c

LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_tcs
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

