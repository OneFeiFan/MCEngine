//
// Created by 25843 on 2023/7/20.
//
#ifndef MCENGINE_LOG_COO

#include <c++/v1/string>
#include "log.h"
#include "JavaAtach.h"
#include "NativeEngine.h"

void log::writeFile() {

}

void log::LogError(char *, std::string) {

}
std::string log::JStringTransfer(jstring jStr) {
    JNIEnv* env = JavaAtach::attach();
    if (!jStr) return "";
    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));
    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
    env->DeleteLocalRef(stringJbytes); env->DeleteLocalRef(stringClass);
    return ret;
}
char* log::jstringToChar(jstring jstr) {
    JNIEnv* env = JavaAtach::attach();
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

void log::Toast(JNIEnv* env, std::string str) {
    /*env = JavaAtach::attach();
    jclass HookEngineptr = env->FindClass("com/taolesi/mcengine/HookEngine");
    jmethodID id = env -> GetStaticMethodID(HookEngineptr, "Toast", "(Ljava/lang/String;)V");
    const char* _charName = str.c_str();
    jstring _jName = env -> NewStringUTF(_charName);
    env -> CallStaticVoidMethod(HookEngineptr, id, _jName);*/
}
#endif