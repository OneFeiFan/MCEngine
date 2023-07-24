#ifndef JNI_2_NATIVE_HPP
#define JNI_2_NATIVE_HPP

#include <vector>
#include <jni.h>
#include <dlfcn.h>
#include "headers/BlockPos.h"
#include "includes/EXHookFR.h"
std::vector<int> forbiddenIDPool, barrelIDPool;
#define invokeCallback(CallbackClass, name, signature, args...)                \
    {                                                                          \
        JNIEnv *env = EXHookFR::hookerPtr->getENV();                           \
        jmethodID id = env->GetStaticMethodID(CallbackClass, name, signature); \
        env->CallStaticVoidMethod(CallbackClass, id, ##args);                  \
    };

extern "C"
{
    JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *)
    {
        EXHookFR::jvm = vm;
        freopen("/storage/emulated/0/tmp/loglog.txt", "w", stdout);
        void *handle = dlopen("libminecraftpe.so", RTLD_NOW | RTLD_NOLOAD); // RTLD_DEFAULT;//
        if (handle)
        {
            EXHookFR hooker(handle);
            EXHookFR::hookerPtr = &hooker;
            hooker.init();
            // printf("加载成功");
        }

        return JNI_VERSION_1_6;
    }
[[maybe_unused]] void setDobbySymbolResolver(void *symbol)
    {
        my_DobbySymbolResolver = (void *(*)(const char *, const char *))symbol;
    }
[[maybe_unused]] void setDobbyHook(void *symbol)
    {
        my_DobbyHook = (int (*)(void *, void *, void *))symbol;
    }
    //    JNIEXPORT void JNICALL Java_com_taolesi_natives_NativeAPI_define(JNIEnv *env, jclass clazz)
    //    {
    //        EXHookFR::hookerPtr->Class = (jclass)env->NewGlobalRef(clazz);
    //    };
    //    JNIEXPORT jint JNICALL Java_com_taolesi_natives_NativeBlockPos_getX(JNIEnv *env, jobject clz, BlockPos const &pos)
    //    {
    //        return pos.x;
    //    };
    //    JNIEXPORT jint JNICALL Java_com_taolesi_natives_NativeBlockPos_getY(JNIEnv *env, jobject clz, BlockPos const &pos)
    //    {
    //        return pos.y;
    //    };
    //    JNIEXPORT jint JNICALL Java_com_taolesi_natives_NativeBlockPos_getZ(JNIEnv *env, jobject clz, BlockPos const &pos)
    //    {
    //        return pos.z;
    //    };
    //    JNIEXPORT void JNICALL Java_com_taolesi_natives_BarrelDataSet_setForbiddenID(JNIEnv *env, jobject clz, jint id)
    //    {
    //        forbiddenIDPool.push_back(id);
    //    };
    //    JNIEXPORT void JNICALL Java_com_taolesi_natives_BarrelDataSet_setBarrelID(JNIEnv *env, jobject clz, jint id)
    //    {
    //        barrelIDPool.push_back(id);
    //    };
}
#endif