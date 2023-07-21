
LOADE_PATH := $(call my-dir)/loader
EXAMPLE_PATH := $(call my-dir)/example
MCENGINE_PATH := $(call my-dir)/cpp
LOCAL_PATH := $(LOADE_PATH)
include $(CLEAR_VARS)
LOCAL_CPP_FEATURES += exceptions
LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/includes/*)
LOCAL_C_INCLUDES +=	$(wildcard $(LOCAL_PATH)/headers/*)
#LOCAL_C_INCLUDES是储存项目头文件的路径，如果你增加路目录，也请在此修改
LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := loader
#LOCAL_MODULE是模块名，可自定义
SRC_FILS := $(wildcard $(LOCAL_PATH)/*/*.c $(LOCAL_PATH)/*/*.cpp $(LOCAL_PATH)/*.cpp $(LOCAL_PATH)/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*/*.cpp)
#SRC_FILS是储存项目中c/cpp文件相对路径的变量，支持从jni往下搜索1层的.c文件和jni往下0~4层的cpp文件
LOCAL_SRC_FILES := $(SRC_FILS:$(LOCAL_PATH)/%=%)
#LOCAL_SRC_FILES是储存SRC_FILS中文件绝对路径的变量
LOCAL_LDLIBS     := -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI) -ldobby
#LOCAL_LDLIBS是用于连接的变量
include $(BUILD_SHARED_LIBRARY)


LOCAL_PATH := $(EXAMPLE_PATH)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/includes/*)
LOCAL_C_INCLUDES +=	$(wildcard $(LOCAL_PATH)/headers/*)
#LOCAL_C_INCLUDES是储存项目头文件的路径，如果你增加路目录，也请在此修改
LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := example
#LOCAL_MODULE是模块名，可自定义
SRC_FILS := $(wildcard $(LOCAL_PATH)/*/*.c $(LOCAL_PATH)/*/*.cpp $(LOCAL_PATH)/*.cpp $(LOCAL_PATH)/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*/*.cpp)
#SRC_FILS是储存项目中c/cpp文件相对路径的变量，支持从jni往下搜索1层的.c文件和jni往下0~4层的cpp文件
LOCAL_SRC_FILES := $(SRC_FILS:$(LOCAL_PATH)/%=%)
#LOCAL_SRC_FILES是储存SRC_FILS中文件绝对路径的变量
LOCAL_LDLIBS    := -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI) -llog
#LOCAL_LDLIBS是用于连接的变量
include $(BUILD_SHARED_LIBRARY)


LOCAL_PATH := $(MCENGINE_PATH)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += $(wildcard $(LOCAL_PATH)/includes/*)
LOCAL_C_INCLUDES +=	$(wildcard $(LOCAL_PATH)/headers/*)
#LOCAL_C_INCLUDES是储存项目头文件的路径，如果你增加路目录，也请在此修改
LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := mcengine
#LOCAL_MODULE是模块名，可自定义
SRC_FILS := $(wildcard $(LOCAL_PATH)/*/*.c $(LOCAL_PATH)/*/*.cpp $(LOCAL_PATH)/*.cpp $(LOCAL_PATH)/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*.cpp $(LOCAL_PATH)/*/*/*/*/*.cpp)
#SRC_FILS是储存项目中c/cpp文件相对路径的变量，支持从jni往下搜索1层的.c文件和jni往下0~4层的cpp文件
LOCAL_SRC_FILES := $(SRC_FILS:$(LOCAL_PATH)/%=%)
#LOCAL_SRC_FILES是储存SRC_FILS中文件绝对路径的变量
LOCAL_LDLIBS    := -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI) -llog
#LOCAL_LDLIBS是用于连接的变量
include $(BUILD_SHARED_LIBRARY)
