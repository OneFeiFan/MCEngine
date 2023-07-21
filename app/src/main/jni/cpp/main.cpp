#include <jni.h>
#include <dlfcn.h>
#include <cstring>
#include <malloc.h>
#include <c++/v1/string>
#include "JavaAtach.h"

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *unused) {
    JavaAtach::init(vm);
    return JNI_VERSION_1_6;
}
