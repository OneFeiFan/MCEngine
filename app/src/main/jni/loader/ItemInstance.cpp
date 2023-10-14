#include <jni.h>
#include <iostream>
#include "headers/Fake_ItemInstance.hpp"
#include "includes/dobby.h"

//
// Created by 25843 on 2023/10/14.
//
#define JniExport(type, Class, args...) JNIEXPORT type JNICALL Java_com_taolesi_mcengine_##Class(JNIEnv *env, jclass clazz, ##args)

extern "C" {
JniExport(jlong*, mod_ItemInstance_get, jlong item_ptr)
{
    return (jlong*) fake_ItemInstance_Item(*(Item*) item_ptr);
}
}