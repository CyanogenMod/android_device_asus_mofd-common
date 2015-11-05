LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := liblog libcutils libui libgui libbinder libutils

LOCAL_SRC_FILES := \
    graphic-buffer.cpp \
    mofd_camera.c \
    surface-control.cpp \

LOCAL_MODULE := libshim_camera
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)
