LOCAL_PATH := $(call my-dir)

#zt_update
include $(CLEAR_VARS)

LOCAL_SRC_FILES :=                  \
    src/TCP/client.cpp              \
    src/TCP/server.cpp              \
	src/daemon/fileDaemon.cpp		\
	src/main.cpp

LOCAL_MODULE := daemonProc

LOCAL_MODULE_TAGS := daemonProc


LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/src/daemon \
    $(LOCAL_PATH)/src/TCP

LOCAL_EXPORT_C_INCLUDES:=$(LOCAL_C_INCLUDES)
LOCAL_LDLIBS += -ldl

#LOCAL_CPPFLAGS += -std=c++11
LOCAL_CPPFLAGS +=  -Wno-literal-suffix 
LOCAL_CFLAGS +=  -Wl,--no-as-needed
LOCAL_CFLAGS +=  -std=c++11
LOCAL_CFLAGS +=  -pthread

LOCAL_CFLAGS += -fopenmp -O2 
LOCAL_CFLAGS += -march=armv7-a -mfloat-abi=softfp -mfpu=neon

include $(BUILD_EXECUTABLE)
