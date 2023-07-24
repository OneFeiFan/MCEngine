#include "headers/ProcessView.h"
#include "includes/dobby.h"
#include <jni.h>
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <cstdio>
#include "headers/miniz.h"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
void UnZip(const char *s_Test_archive_filename)
{
    mz_bool status;
    auto *zip_archive = new mz_zip_archive();
    void *p;
    namespace fs = std::filesystem;
    //memset(&zip_archive, 0, sizeof(zip_archive));
    status = mz_zip_reader_init_file(zip_archive, s_Test_archive_filename, 0);
    if(!status){
        printf("mz_zip_reader_init_file() failed!\n");
        return;
    }
    fs::remove_all("/data/data/com.mojang.minecraftpe/MCEngine/");
    for(int i = 0; i < (int) mz_zip_reader_get_num_files(zip_archive); ++i){
        mz_zip_archive_file_stat file_stat;
        if(!mz_zip_reader_file_stat(zip_archive, i, &file_stat)){
            printf("mz_zip_reader_file_stat() failed!\n");
            mz_zip_reader_end(zip_archive);
            return;
        }
        if(!mz_zip_reader_is_file_a_directory(zip_archive, i)){
            p = mz_zip_reader_extract_file_to_heap(zip_archive, file_stat.m_filename, &file_stat.m_uncomp_size, 0);
            if(!p){
                printf("mz_zip_reader_extract_file_to_heap() failed!\n");
                mz_zip_reader_end(zip_archive);
                return;
            }
            std::string directoryName("/data/data/com.mojang.minecraftpe/MCEngine/");
            fs::path path(directoryName + file_stat.m_filename);
            fs::path direction = path.parent_path();
            if(!fs::exists(direction)){
                fs::create_directories(direction);
                std::cout<<direction.c_str()<<std::endl;
            }
            std::ofstream ofs(path, std::ios::out | std::ios::binary);
            ofs.write((const char *) p, (int)file_stat.m_uncomp_size);
            ofs.close();
            mz_free(p);
        }
    }
    mz_zip_reader_end(zip_archive);
}

//const char *linkerName;
void *symbol = nullptr;
JavaVM *loaderVM = nullptr;
void *loaderPtr = nullptr;

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
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *ptr)
{
    freopen("/storage/emulated/0/tmp/log1.txt", "w", stdout);
    //linkerName = "linker64";
    loaderVM = vm;
    loaderPtr = ptr;
    symbol = DobbySymbolResolver("linker", "__loader_android_dlopen_ext");
    return JNI_VERSION_1_6;
}
JNIEXPORT void JNICALL Java_com_taolesi_mcengine_HookEngine_setDL(JNIEnv *env, [[maybe_unused]] jclass clazz, jstring dlpath)
{
    UnZip(jstringToChar(env, dlpath));
    try{
        utils::ProcessView processObj;
        [[maybe_unused]] int temp = processObj.readProcess(getpid());
        if(symbol){
            auto *(*my_android_dlopen_ext)(const char *, int, void *, void *) = (void *(*)(const char *, int, void *, void *)) symbol;
            for(int i = 0; i < processObj.getModules().size(); ++i){
                if(processObj.getModules()[i].name == "libminecraftpe.so"){
                    void *handle = my_android_dlopen_ext(strcat(jstringToChar(env, dlpath), "!/lib/armeabi-v7a/libnativecore.so"), RTLD_NOW, nullptr, (void *) processObj.getModules()[i].baseAddress);
                    void *mcengineHandle = dlopen("libmcengine.so", RTLD_NOW | RTLD_NOLOAD);
                    auto (*Toast)(std::string) = (void (*)(std::string)) dlsym(mcengineHandle, "log_Toast");
                    //
                    if(handle){
                        Toast("成功加载native核心");
                        auto (*my_JNI_OnLoad)(JavaVM *, void *) = (jint (*)(JavaVM *, void *)) dlsym(handle, "JNI_OnLoad");
                        auto (*hook_setDobbySymbolResolver)(void *) = (void (*)(void *)) dlsym(handle, "setDobbySymbolResolver");
                        auto (*hook_setDobbyHook)(void *) = (void (*)(void *)) dlsym(handle, "setDobbyHook");

                        hook_setDobbySymbolResolver((void *) DobbySymbolResolver);
                        hook_setDobbyHook((void *) DobbyHook);
                        //首先进行Dobby方法传递，然后才能初始化
                        my_JNI_OnLoad(loaderVM, loaderPtr);
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
}