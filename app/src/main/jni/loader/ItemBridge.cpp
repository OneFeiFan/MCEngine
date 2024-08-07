//
// Created by 25843 on 2023/10/13.
//
#include <cstdio>
#include <string>
#include <iostream>
#include <jni.h>
#include <unistd.h>
#include <dlfcn.h>
#include "tester/android.hpp"
#include "tester/log.hpp"
#include "includes/dobby.h"
#include "includes/tools/lua/lua.hpp"
#include "includes/HookFactory/HookFactory.hpp"
#include "includes/ItemFactory/ItemFactory.hpp"
#include "IDPool.hpp"
#include "headers/feifan/ItemRegistryFaker.hpp"
#include "includes/ItemFactory/FoodItemFactory.hpp"
#include "includes/ItemFactory/SwordItemFactory.hpp"

#define JniExport(type, Class, args...) JNIEXPORT type JNICALL Java_com_taolesi_mcengine_##Class(JNIEnv *env, jclass clazz, ##args)

extern "C" {
JniExport(void, NativeClass_NativeItem_define)
{
    IDPool::define(*fake_ItemRegistry_mMaxItemID);
}
JniExport(jlong *, NativeClass_NativeItem_createItem, jstring jname, jstring jiconName, jint jindex, jint jtype)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *iconName = android::jstringToCharArr(env, jiconName);
    return (jlong *) ItemFactory::createObj(name, iconName, jindex, (CreativeItemCategory) jtype);
}
JniExport(jlong *, NativeClass_NativeItem_createFood, jstring jname, jstring jicon, jint index, jint type, jstring jfood_data)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *iconName = android::jstringToCharArr(env, jicon);
    const char *food_data = android::jstringToCharArr(env, jfood_data);
    return (jlong *) FoodItemFactory::createObj(name, iconName, index, (CreativeItemCategory) type, food_data);
}
JniExport(jlong *, NativeClass_NativeItem_createSword, jstring jname, jstring jicon, jint jindex, jint jtype, jstring jtier, jint jdurability, jint jdamage)
{
    const char *name = android::jstringToCharArr(env, jname);
    const char *iconName = android::jstringToCharArr(env, jicon);
    const char *tier = android::jstringToCharArr(env, jtier);
    return (jlong *) SwordItemFactory::createObj(name, iconName, jindex, (CreativeItemCategory) jtype, tier, jdurability, jdamage);
}
JniExport(jshort, mod_Item_getId, jlong item_ptr)
{
    return fake_Item_getId((Item*) item_ptr);
}
JniExport(void, NativeClass_NativeItem_baseItemUseOn, jlong ptr, jlong itemstack, jlong actor, jint x, jint y, jint z, jshort d, jfloat e, jfloat f, jfloat g)
{
    base_Item_useOn((Item *) ptr, (ItemStack *) itemstack, (Actor *) actor, x, y, z, d, e, f, g);
}

JniExport(jboolean, mod_Item_isSeed, jlong item_ptr)
{
    return fake_Item_isSeed((Item *) item_ptr);
}
}
