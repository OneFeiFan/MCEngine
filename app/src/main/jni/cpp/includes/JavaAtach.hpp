#ifndef JAVAATACH_HPP
#define JAVAATACH_HPP
#include <jni.h>

class JavaAtach {
public:
    static JavaVM* jvm;
    static JNIEnv* attach(){
        JNIEnv* env = nullptr;
        int attachStatus = jvm->GetEnv((void**) &env, JNI_VERSION_1_6);
        if (attachStatus == JNI_EDETACHED) {
            jvm -> AttachCurrentThread(&env, nullptr);
        }
        return env;
    };
    static void init(JavaVM* vm){
        jvm = vm;
    };
};

JavaVM* JavaAtach::jvm = nullptr;
#endif