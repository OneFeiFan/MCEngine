//
// Created by 30225 on 2023/7/25.
//
#ifndef MCENGINE_JNI2NATIVE_HPP
#define MCENGINE_JNI2NATIVE_HPP

#include <cstdio>
#include <string>
#include <string.h>
#include <iostream>
#include <jni.h>
#include <unistd.h>
#include <dlfcn.h>
//#include <sys/stat.h>
//#include <sys/types.h>
#include "tester/android.hpp"
#include "tester/log.hpp"
//#include "includes/QA/ProcessView.h"
#include "includes/dobby.h"
//#include "includes/Unzip/Unzip.h"
#include "includes/lua/lua.hpp"
#include "includes/NC_HookFR/NCHookFR.hpp"
#include "includes/NC_Items/NC_Items.hpp"
#include "NC_FoodItems.hpp"
#include "NC_SwordItems.hpp"
#include "NativeClass.hpp"
#include "NC_Blocks.hpp"
#include "IDPool.hpp"
#include "headers/Fake_ItemRegistry.hpp"

#define JniExport(type, Class, args...) JNIEXPORT type JNICALL Java_com_taolesi_mcengine_##Class(JNIEnv *env, jclass clazz, ##args)

extern "C" {
int add(lua_State *L)
{
    int a = lua_tointeger(L, 1);
    int b = lua_tointeger(L, 2);
    int result = a + b;
    lua_pushinteger(L, result);
    return 1;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]]void *reserved)
{
    freopen("/storage/emulated/0/tmp/log1.txt", "w", stdout);

    android::setJavaVM(vm);
    JNIEnv *env = android::getJNIEnv();

//    const char *a = android::getExternalFilePath(android::getJNIEnv(), "", android::getApplicationContext(android::getJNIEnv()));
//    std::string b = std::string(a) + "/c01log.log";
//    Logger::instance = new Logger(b.c_str());
//
//    Logger::instance->log("log sys init success.");
//    void*ptr=dlopen("libminecraftpe.so", RTLD_LAZY);
//
//    Logger::instance->log("ptr = "+std::to_string(reinterpret_cast<uintptr_t>(ptr)));



//// 这边留一个log的使用例子
    void *mcHandleFake = DobbySymbolResolver("libminecraftpe.so", "_ZNK5Actor9getRegionEv");
    //android::showToast(env, android::charArrToJstring(env, std::to_string(reinterpret_cast<uintptr_t>(mcHandleFake)).c_str()));
    if(mcHandleFake){
//            lua_State *L = luaL_newstate();
//            luaL_openlibs(L);
//            lua_pushcfunction(L, add);
//            lua_setglobal(L, "add");
//
////            加载并执行
////            Lua 脚本文件
//            if(luaL_dofile(L, "/storage/emulated/0/tmp/script.lua") != LUA_OK){
//                printf("Failed to load and execute script.lua: %s\n", lua_tostring(L, -1));
//                lua_close(L);
//            }else {
//                printf("成功");
//            }
//            lua_close(L);
        android::showToast(env, android::charArrToJstring(env, "成功加载native核心"));
        android::showToast(env, android::charArrToJstring(env, "成功加载native核心"));
        NCHookFR::jvm = vm;
        NCHookFR hooker;
        NCHookFR::hookerPtr = &hooker;
        hooker.init();
        //}

    }else {
        android::showToast(env, android::charArrToJstring(env, "未能加载native核心"));
    }

    return JNI_VERSION_1_6;
}
JniExport(jlong*, NativeClass_NativeItem_createItem, jstring jname, jstring jiconName, jint jindex, jint jtype)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *iconName = android::jstringToCharArr(env, jiconName);
    return (jlong *) NC_Items::createObj(name, iconName, jindex, (CreativeItemCategory) jtype);
}
JniExport(jlong*, NativeClass_NativeItem_createFood, jstring jname, jstring jicon, jint index, jint type, jstring jfood_data)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *iconName = android::jstringToCharArr(env, jicon);
    const char *food_data = android::jstringToCharArr(env, jfood_data);
    return (jlong *) NC_FoodItems::createObj(name, iconName, index, (CreativeItemCategory) type, food_data);
}
JniExport(jlong*, NativeClass_NativeItem_createSword, jstring jname, jstring jicon, jint jindex, jint jtype, jstring jtier, jint jdurability, jint jdamage)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *iconName = android::jstringToCharArr(env, jicon);
    const char *tier = android::jstringToCharArr(env, jtier);
    return (jlong *) NC_SwordItems::createObj(name, iconName, jindex, (CreativeItemCategory) jtype, tier, jdurability, jdamage);
}
JniExport(void, NativeClass_NativeItem_baseItemUseOn, jlong ptr, jlong itemstack, jlong actor, jint x, jint y, jint z, jshort d, jfloat e, jfloat f, jfloat g)
{
    base_Item_useOn((Item *) ptr, (ItemStack *) itemstack, (Actor *) actor, x, y, z, d, e, f, g);
}
JniExport(void, NativeClass_NativeItem_define)
{
    NativeClass::NativeItem = (jclass) env->NewGlobalRef(clazz);
    IDPool::define(*fake_ItemRegistry_mMaxItemID);
}
JniExport(void, NativeClass_NativeBlock_createBlock, jstring jname, jstring jTextureName, jint jTextureData, jint jtype, jstring jMaterial)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *textureName = android::jstringToCharArr(env, jTextureName);
    const char *material = android::jstringToCharArr(env, jMaterial);
    NC_Blocks::createObj(name, textureName, jTextureData, (CreativeItemCategory) jtype, material);
}
JniExport(short, NativeClass_NativeItem_getId, jstring jname)
{
    //return fake_Item_getId((Item*)ptr);
    return IDPool::getId(android::jstringToCharArr(env, jname));
}
}
#endif