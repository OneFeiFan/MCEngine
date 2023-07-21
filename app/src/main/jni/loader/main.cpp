#include "headers/ProcessView.h"
#include "includes/dobby.h"
#include "../cpp/log.h"
#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
const char *linkerName;
void *symbol = nullptr;
JavaVM *loaderVM = nullptr;
void * loaderPtr = nullptr;
char *jstringToChar(JNIEnv *env, jstring jstr)
{
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char *)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
};


extern "C"
{

    JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void * ptr)
    {
        freopen("/storage/emulated/0/tmp/log.txt", "w", stdout);
        if constexpr (sizeof(void *) == 8)
        {
            linkerName = "linker64";
        }
        else
        {
            linkerName = "linker";
        }
        loaderVM = vm;
        loaderPtr = ptr;
        symbol = DobbySymbolResolver(linkerName, "__loader_android_dlopen_ext");
        return JNI_VERSION_1_6;
    }
    JNIEXPORT void JNICALL Java_com_taolesi_mcengine_HookEngine_setDL(JNIEnv *env, jclass clazz, jstring dlpath)
    {
        utils::ProcessView processObj;
        int temp = processObj.readProcess(getpid());
        if (symbol)
        {
            void *(*my___loader_android_dlopen_ext)(const char *, int, void *, void *) = (void *(*)(const char *, int, void *, void *))symbol;
            for (int i = 0; i < processObj.getModules().size(); ++i)
            {
                if (processObj.getModules()[i].name == "libminecraftpe.so")
                {
                    void *handle =  my___loader_android_dlopen_ext(strcat(jstringToChar(env, dlpath), "!/lib/armeabi-v7a/libexample.so"), RTLD_NOW, nullptr, (void *)processObj.getModules()[i].baseAddress);
                    //log::Toast("已取得句柄");
                    jint (*my_JNI_OnLoad)(JavaVM *,void *)=(jint (*)(JavaVM *, void *))dlsym(handle,"JNI_OnLoad");
                    my_JNI_OnLoad(loaderVM,loaderPtr);
                    
                    break;
                }
            }
        }
    }
}