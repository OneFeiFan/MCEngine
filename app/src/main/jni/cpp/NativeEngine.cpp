#ifndef _NATIVEENGINE_CPP

#include <cstdarg>
#include <cstdlib>

#include "NativeEngine.h"
#include "JavaAtach.h"
#include <c++/v1/string>

jclass NativeEngine::HookEngineptr = nullptr;

jclass NativeEngine::HookEngineClass() {
    return HookEngineptr;
}
jclass NativeEngine::HookEngineClass(JNIEnv* env) {
    jclass tempRef = env->FindClass("com/taolesi/mcengine/HookEngine");
    HookEngineptr = static_cast<jclass>(env->NewGlobalRef(tempRef));
    env->DeleteLocalRef(tempRef);
    return HookEngineptr;
}
void NativeEngine::Log(std::string claz, int a) {
    JNIEnv* env = JavaAtach::attach();
    jclass HookEngineptr = NativeEngine::HookEngineClass();
    jmethodID id = env -> GetStaticMethodID(HookEngineptr, "Log", "(Ljava/lang/String;I)V");
    const char* charName = claz.c_str();
    jstring jName = env -> NewStringUTF(charName);
    env -> CallStaticVoidMethod(HookEngineptr, id, jName, (jint) a);
}
void NativeEngine::Log(std::string claz, float a) {
    JNIEnv* env = JavaAtach::attach();
    jclass HookEngineptr = NativeEngine::HookEngineClass();
    jmethodID id = env -> GetStaticMethodID(HookEngineptr, "Log", "(Ljava/lang/String;F)V");
    const char* charName = claz.c_str();
    jstring jName = env -> NewStringUTF(charName);
    env -> CallStaticVoidMethod(HookEngineptr, id, jName, (jfloat) a);
}
void NativeEngine::Log(std::string claz, long a) {
    JNIEnv* env = JavaAtach::attach();
    jclass HookEngineptr = NativeEngine::HookEngineClass();
    jmethodID id = env -> GetStaticMethodID(HookEngineptr, "Log", "(Ljava/lang/String;J)V");
    const char* charName = claz.c_str();
    jstring jName = env -> NewStringUTF(charName);
    env -> CallStaticVoidMethod(HookEngineptr, id, jName, (jlong) a);
}
void NativeEngine::Log(std::string claz, std::string a) {
    JNIEnv* env = JavaAtach::attach();
    jclass HookEngineptr = NativeEngine::HookEngineClass();
    jmethodID id = env -> GetStaticMethodID(HookEngineptr, "Log", "(Ljava/lang/String;Ljava/lang/String;)V");
    const char* charName = claz.c_str();
    jstring jName = env -> NewStringUTF(charName);
    const char* _charName = a.c_str();
    jstring _jName = env -> NewStringUTF(_charName);
    env -> CallStaticVoidMethod(HookEngineptr, id, jName, _jName);
}
#endif