#include "EXHookFR.h"
#include <cstdio>
#include <iostream>
EXHookFR *EXHookFR::hookerPtr;
JavaVM *EXHookFR::jvm;
[[maybe_unused]] jclass EXHookFR::Class;
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

void InLineHook(void *hook, void *original, const char *symbol_name)
{
    void *ptr = my_DobbySymbolResolver("libminecraftpe.so", symbol_name);
    if (ptr != nullptr)
    {
        printf("成功获取符号：%s的地址\n", symbol_name);
        if (my_DobbyHook(ptr, hook, original) == 0)
        {
            printf("hook成功\n");
        }
        else
        {
            printf("hook失败\n");
        }
    }
    else
    {
        printf("无法获取符号：%s的地址\n", symbol_name);
    }
}
void FakeNative(void **fake_fun,const char *symbol_name)
{
    if(fake_fun){
        void *symbol = my_DobbySymbolResolver("libminecraftpe.so",symbol_name);
        if(symbol!= nullptr){
            printf("成功获取符号：%s的地址\n",symbol_name);
            *fake_fun = symbol;
            printf("fake成功\n");
        }else{
            printf("未能获取符号：%s的地址\n",symbol_name);
            printf("fake失败\n");
        }
    }
}