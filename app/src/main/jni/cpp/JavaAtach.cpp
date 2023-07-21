#ifndef _JAVAATACH_CPP
#define _JAVAATACH_CPP

#include <jni.h>
#include "JavaAtach.h"

JavaVM* JavaAtach::jvm = nullptr;
JNIEnv* JavaAtach::attach() {
    JNIEnv* env = nullptr;
    int attachStatus = jvm->GetEnv((void**) &env, JNI_VERSION_1_6);
    if (attachStatus == JNI_EDETACHED) {
        jvm -> AttachCurrentThread(&env, nullptr);
    }
    return env;
};
void JavaAtach::init(JavaVM* vm) {
    jvm = vm;
};
#endif