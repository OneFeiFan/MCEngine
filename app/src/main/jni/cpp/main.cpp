#include <jni.h>
#include <dlfcn.h>
#include <cstring>
#include <malloc.h>
#include <c++/v1/string>

#include "JavaAtach.h"
#include "log.h"
#include "NativeEngine.h"


extern "C" {
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *unused) {
    JavaAtach::init(vm);
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL
Java_com_taolesi_mcengine_HookEngine_define(JNIEnv *env, jclass clazz) {
    NativeEngine::HookEngineClass(env);
}
void log_Toast(JNIEnv* env, std::string str) {
    log::Toast(env, str);
}
}