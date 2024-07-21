#include <jni.h>
#include <dlfcn.h>
#include <cstring>
#include <malloc.h>
#include <c++/v1/string>
#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <iostream>

#include "tester/android.hpp"
#include "tester/log.hpp"
#include "includes/JavaAtach.hpp"
#include "includes/NativeEngine.hpp"

extern "C" {
    JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *unused) {
        JavaAtach::init(vm);
        android::setJavaVM(vm);
        return JNI_VERSION_1_6;
    }
    JNIEXPORT void JNICALL Java_com_taolesi_mcengine_Loader_define(JNIEnv *env, jclass clazz) {
        NativeEngine::HookEngineClass(env);
    }
}