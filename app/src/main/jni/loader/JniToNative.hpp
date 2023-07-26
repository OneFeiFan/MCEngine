//
// Created by 30225 on 2023/7/25.
//
#ifndef MCENGINE_JNI2NATIVE_HPP
#define MCENGINE_JNI2NATIVE_HPP

#include <cstdio>
#include <string>
#include <iostream>
#include <jni.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "includes/QA/ProcessView.h"
#include "includes/dobby.h"
#include "includes/Unzip/Unzip.h"
#include "includes/lua/lua.hpp"
#include "includes/NC_HookFR/NCHookFR.h"
#include "includes/NC_Items/NC_items.h"

//const char *linkerName;
void *symbol = nullptr;
JavaVM *loaderVM = nullptr;
void *loaderPtr = nullptr;
void *NC_handle;
void *mcengineHandle;


char *jstringToChar(JNIEnv *env, jstring jstr)
{
    char *rtn = nullptr;
    jclass class_string = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(class_string, "getBytes", "(Ljava/lang/String;)[B");
    auto barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if(alen > 0){
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

extern "C" {
int add(lua_State *L)
{
    int a = lua_tointeger(L, 1);
    int b = lua_tointeger(L, 2);
    int result = a + b;
    lua_pushinteger(L, result);
    return 1;
}
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *ptr)
{
    freopen("/storage/emulated/0/tmp/log1.txt", "w", stdout);
    //linkerName = "linker64";
    loaderVM = vm;
    loaderPtr = ptr;
    symbol = DobbySymbolResolver("linker", "__loader_android_dlopen_ext");
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL Java_com_taolesi_mcengine_HookEngine_setDL(JNIEnv *env, jobject clazz, jstring dlpath)
{
    UnZip(jstringToChar(env, dlpath));
    try{
        utils::ProcessView processObj;
        [[maybe_unused]] int temp = processObj.readProcess(getpid());
        if(symbol){
            auto *(*my_android_dlopen_ext)(const char *, int, void *, void *) = (void *(*)(const char *, int, void *, void *)) symbol;
            for(int i = 0; i < processObj.getModules().size(); ++i){
                if(processObj.getModules()[i].name == "libminecraftpe.so"){
                    NC_handle = my_android_dlopen_ext(strcat(jstringToChar(env, dlpath), "!/lib/armeabi-v7a/libnativecore.so"), RTLD_NOW, nullptr, (void *) processObj.getModules()[i].baseAddress);
                    mcengineHandle = dlopen("libmcengine.so", RTLD_NOW | RTLD_NOLOAD);
                    auto (*Toast)(std::string) = (void (*)(std::string)) dlsym(mcengineHandle, "log_Toast");
                    std::cout << strcat(jstringToChar(env, dlpath), "!/lib/armeabi-v7a/libnativecore.so") << std::endl;
                    if(NC_handle){
//                        lua_State *L = luaL_newstate();
//                        luaL_openlibs(L);
//                        lua_pushcfunction(L, add);
//                        lua_setglobal(L, "add");
//                        // 加载并执行 Lua 脚本文件
//                        if(luaL_dofile(L, "/storage/emulated/0/tmp/script.lua") != LUA_OK){
//                            printf("Failed to load and execute script.lua: %s\n", lua_tostring(L, -1));
//                            lua_close(L);
//
//                        }else {
//                            printf("成功");
//                        }
//
//                        lua_close(L);
                        auto (*NC_NativeCoreLoad)(void **) = (void (*)(void **)) dlsym(NC_handle, "NativeCoreLoad");
                        auto (*NC_setDobbySymbolResolver)(void *) = (void (*)(void *)) dlsym(NC_handle, "setDobbySymbolResolver");
                        auto (*NC_setDobbyHook)(void *) = (void (*)(void *)) dlsym(NC_handle, "setDobbyHook");
                        NC_setDobbySymbolResolver((void *) DobbySymbolResolver);
                        NC_setDobbyHook((void *) DobbyHook);
                        //首先进行Dobby方法传递，然后才能初始化
                        NC_InLineHook = (void (*)(void *, void *, const char *)) dlsym(NC_handle, "InLineHook");
                        NC_FakeNative = (void (*)(void **, const char *)) dlsym(NC_handle, "FakeNative");
                        //将native中的两个方法拿到此处，确保方法在此处调用的同时，又可让对面dobby获得mc句柄
                        void *MC_handle  = nullptr;
                        NC_NativeCoreLoad((void **)&MC_handle);
                        //std::cout<<MC_handle<<std::endl;
                        if(MC_handle != nullptr){
                            Toast("成功加载native核心");
                            Toast("成功加载native核心");
                            NCHookFR::jvm = loaderVM;
                            NCHookFR hooker(MC_handle);
                            NCHookFR::hookerPtr = &hooker;
                            hooker.init();
                        }
                        jclass HookEngineptr = env->FindClass("com/taolesi/mcengine/HookEngine");
                        jmethodID id = env->GetMethodID(HookEngineptr, "runCoreJS", "()V");
                        env->CallVoidMethod(clazz, id);

                    }else {
                        Toast("未能加载native核心");
                    }
                    break;
                }
            }
        }
    }
    catch(const std::exception &e){
        std::cerr << e.what() << '\n';
    }

}
JNIEXPORT void JNICALL
Java_com_taolesi_mcengine_NativeItem_createItem(JNIEnv *env, [[maybe_unused]] jclass clazz, jstring jname, jstring jiconName, jint jindex, jboolean is2category, jint jtype)
{
    const char *name = jstringToChar(env, jname);
    const char *iconName = jstringToChar(env, jiconName);
    CreativeItemCategory type;
    switch(jtype){
        case 0: type = CreativeItemCategory::All_3;
            break;
        case 1:
            type = CreativeItemCategory::Construction;
            break;
        case 2:
            type = CreativeItemCategory::Nature;
            break;
        case 3:
            type = CreativeItemCategory::Equipment;
            break;
        case 4:
            type = CreativeItemCategory::Items;
            break;
        case 5:
            type = CreativeItemCategory::ItemCommandOnly;
            break;
        case 6:
            type = CreativeItemCategory::Undefined_10;
            break;
        case 7:
            type = CreativeItemCategory::NUM_CATEGORIES;
            break;
        default:
            type = CreativeItemCategory::Construction;
            break;
    };
    NC_Items::createNCIObject(name, iconName, jindex, is2category, type);
}
}
#endif //MCENGINE_JNI2NATIVE_1HPP
//#define invokeCallback(CallbackClass, name, signature, args...)                \
//    {                                                                          \
//        JNIEnv *env = EXHookFR::hookerPtr->getENV();                           \
//        jmethodID id = env->GetStaticMethodID(CallbackClass, name, signature); \
//        env->CallStaticVoidMethod(CallbackClass, id, ##args);                  \
//    };