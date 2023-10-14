#include <jni.h>
#include "headers/Fake_Actor.hpp"

//
// Created by 25843 on 2023/10/14.
//
#define JniExport(type, Class, args...) JNIEXPORT type JNICALL Java_com_taolesi_mcengine_##Class(JNIEnv *env, jclass clazz, ##args)


extern "C" {
JniExport(jboolean, mod_Actor_isSneaking, jlong actor_ptr)
{
    return fake_Actor_isSneaking((Actor*) actor_ptr);
}
}