LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE           := roadtosystem
LOCAL_C_INCLUDES       := $(LOCAL_PATH)/src
LOCAL_SRC_FILES        := src/roadtosystem_jni.c
LOCAL_CFLAGS           := -std=c99
LOCAL_LDFLAGS          := -llog -ldl -L$(LOCAL_PATH)/libs/$(APP_ABI)
include $(BUILD_SHARED_LIBRARY)
