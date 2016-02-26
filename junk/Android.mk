LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := loop.c
LOCAL_MODULE := loop

include $(BUILD_EXECUTABLE)
