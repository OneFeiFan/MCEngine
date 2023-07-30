NDK_TOOLCHAIN_VERSION := clang
APP_STL := c++_static
#APP_STL指连接方式
APP_PLATFORM := android-20
#APP_PLATFORM定义使用的ndk库函数版本号
APP_ABI := armeabi-v7a
# APP_ABI是指架构
APP_CPPFLAGS += -std=c++17 -fdeclspec

