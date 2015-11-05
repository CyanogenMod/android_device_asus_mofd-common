LOCAL_PATH := $(call my-dir)

# Camera

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    graphic-buffer.cpp \
    sensor-manager.c \
    surface-control.cpp

LOCAL_SHARED_LIBRARIES := liblog libcutils libui libgui libbinder libutils
LOCAL_MODULE := libshim_camera
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)

# GPSD

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    crypto_malloc.c \
    icu53.c \
    sensor-manager.c

LOCAL_SHARED_LIBRARIES := liblog libcutils libui libgui libbinder libutils libicuuc libicui18n
LOCAL_MODULE := libshim_gpsd
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)

# MMGR

include $(CLEAR_VARS)

LOCAL_SRC_FILES := icu53.c
LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_mmgr
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

# sensors

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
     icu53.c

LOCAL_SHARED_LIBRARIES := libicuuc libicui18n
LOCAL_MODULE := libshim_sensors
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

