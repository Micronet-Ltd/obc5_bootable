# Copyright 2009 The Android Open Source Project

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := mcu_update.cpp
LOCAL_MODULE := mcu_ua
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_C_INCLUDES += bootable/recovery
LOCAL_STATIC_LIBRARIES := libz
LOCAL_STATIC_LIBRARIES += libcutils libstdc++ libc

include $(BUILD_EXECUTABLE)
