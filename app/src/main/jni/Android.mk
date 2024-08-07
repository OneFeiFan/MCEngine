LOADE_PATH := $(call my-dir)/loader
MCENGINE_PATH := $(call my-dir)/cpp

LOCAL_PATH := $(MCENGINE_PATH)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/includes/*)
LOCAL_C_INCLUDES +=	$(wildcard $(LOCAL_PATH)/headers/*)
LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := mcengine
SRC_FILS := $(wildcard $(LOCAL_PATH)/*/*.c $(LOCAL_PATH)/*/*.cpp $(LOCAL_PATH)/*.cpp $(LOCAL_PATH)/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*/*.cpp)
LOCAL_SRC_FILES := $(SRC_FILS:$(LOCAL_PATH)/%=%)
LOCAL_LDLIBS    := -llog
include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(LOADE_PATH)
include $(CLEAR_VARS)
LOCAL_CPP_FEATURES += exceptions
LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/includes/*)
LOCAL_C_INCLUDES +=	$(wildcard $(LOCAL_PATH)/headers/*)
LOCAL_C_INCLUDES +=	$(wildcard $(LOCAL_PATH)/instances/*)
LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := loader
SRC_FILS := $(wildcard $(LOCAL_PATH)/*/*/*.c $(LOCAL_PATH)/*/*.cpp $(LOCAL_PATH)/*.cpp $(LOCAL_PATH)/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*/*.cpp)
LOCAL_SRC_FILES := $(SRC_FILS:$(LOCAL_PATH)/%=%)
LOCAL_LDLIBS     := -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI) -ldobby -llua -lquickjs -landroid
include $(BUILD_SHARED_LIBRARY)