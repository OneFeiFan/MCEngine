#include <jni.h>
#include <dlfcn.h>
#include <cstring>
#include <malloc.h>
#include <c++/v1/string>
#include <filesystem>
#include <iostream>
#include "includes/JavaAtach.h"
#include "includes/log.h"
#include "includes/NativeEngine.h"
#include <unistd.h>
#include <iostream>

extern "C" {
    JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *unused) {
        JavaAtach::init(vm);
        return JNI_VERSION_1_6;
    }
    JNIEXPORT void JNICALL Java_com_taolesi_mcengine_Loader_define(JNIEnv *env, jclass clazz) {
        NativeEngine::HookEngineClass(env);
    }
    void log_Toast(std::string str) {
        log::Toast(str);
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_taolesi_mcengine_Loader_copyToEx(JNIEnv *env, jclass clazz, jstring res, jstring output) {
    try {
        std::filesystem::copy_file(log::jstringToChar(res), log::jstringToChar(output));
    } catch (const std::exception &e) {
        remove(log::jstringToChar(output));
        std::filesystem::copy_file(log::jstringToChar(res), log::jstringToChar(output));
    }
}