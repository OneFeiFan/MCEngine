#include "NCHookFR.h"
#include <cstdio>
#include <iostream>
#include "headers/Fake_Actor.hpp"
#include "headers/Fake_BlockSource.hpp"
#include "headers/Fake_BlockLegacy.hpp"
#include "headers/Fake_ItemStackBase.hpp"
#include "headers/Fake_ItemRegistry.h"
#include "headers/Fake_Item.h"
#include "headers/CreativeItemCategory.h"
#include "includes/dobby.h"
char * mcNativeDir;
NCHookFR *NCHookFR::hookerPtr;
JavaVM *NCHookFR::jvm;
[[maybe_unused]] jclass NCHookFR::Class;
NCHookFR::NCHookFR(){}
JNIEnv *NCHookFR::getENV()
{
    JNIEnv *env = nullptr;
    int attachStatus = NCHookFR::jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    if (attachStatus == JNI_EDETACHED)
    {
        NCHookFR::jvm->AttachCurrentThread(&env, nullptr);
    }
    return env;
}
void NC_InLineHook(void *hook, void **original, const char *symbol_name) {
    void *ptr = DobbySymbolResolver(mcNativeDir, symbol_name);
    if (ptr != nullptr) {
        printf("成功获取符号：%s的地址\n", symbol_name);
        if (DobbyHook(ptr, hook, original) == 0) {
            printf("hook成功\n");
        } else {
            printf("hook失败\n");
        }
    } else {
        printf("无法获取符号：%s的地址\n", symbol_name);
    }
}

void NC_FakeNative(void **fake_fun, const char *symbol_name) {
    if (fake_fun) {
        void *symbol = DobbySymbolResolver(mcNativeDir, symbol_name);
        if (symbol != nullptr) {
            printf("成功获取符号：%s的地址\n", symbol_name);
            *fake_fun = symbol;
            printf("fake成功\n");
        } else {
            printf("未能获取符号：%s的地址\n", symbol_name);
            printf("fake失败\n");
        }
    }
}