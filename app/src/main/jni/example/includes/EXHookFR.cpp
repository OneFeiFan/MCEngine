#include "EXHookFR.hpp"
EXHookFR *EXHookFR::hookerPtr;
JavaVM * EXHookFR::jvm;
jclass EXHookFR::Class;
EXHookFR::EXHookFR(void *handle) : MCHandle(handle) {}
JNIEnv *EXHookFR::getENV()
{
    JNIEnv *env = nullptr;
    int attachStatus = EXHookFR::jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    if (attachStatus == JNI_EDETACHED)
    {
        EXHookFR::jvm->AttachCurrentThread(&env, nullptr);
    }
    return env;
}