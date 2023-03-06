LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := app-integrity-checker
LOCAL_SRC_FILES := app_integrity_checker.cpp

LOCAL_CFLAGS    := -std=c++11 -Wall

LOCAL_LDLIBS    := -llog -lcrypto -lssl

APP_PLATFORM    := android-21

include $(BUILD_SHARED_LIBRARY)
