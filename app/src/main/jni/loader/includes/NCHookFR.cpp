#include "NCHookFR.h"
#include <cstdio>
#include <iostream>
#include "headers/Fake_Actor.hpp"
#include "headers/Fake_BlockSource.hpp"
#include "headers/Fake_BlockLegacy.hpp"
#include "headers/Fake_ItemStackBase.hpp"
#include "headers/Fake_ItemRegistry.hpp"
#include "headers/Fake_Item.hpp"
#include "headers/CreativeItemCategory.h"

NCHookFR *NCHookFR::hookerPtr;
JavaVM *NCHookFR::jvm;
[[maybe_unused]] jclass NCHookFR::Class;
NCHookFR::NCHookFR(void *handle) : MCHandle(handle) {}
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
