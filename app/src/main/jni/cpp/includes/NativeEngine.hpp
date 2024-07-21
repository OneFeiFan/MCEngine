#include <cstdarg>
#include <cstdlib>
#include <c++/v1/string>
#include <jni.h>
#include <c++/v1/string>

class NativeEngine
{
public:
    static jclass HookEngineptr;

    static jclass HookEngineClass(){
        return HookEngineptr;
    };

    static void HookEngineClass(JNIEnv *env){
        jclass tempRef = env->FindClass("com/taolesi/mcengine/HookEngine");
        HookEngineptr = static_cast<jclass>(env->NewGlobalRef(tempRef));
        env->DeleteLocalRef(tempRef);
    };

};
jclass NativeEngine::HookEngineptr = nullptr;