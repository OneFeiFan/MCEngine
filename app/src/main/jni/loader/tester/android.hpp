//
// Created by 30225 on 2023/7/30.
//

#ifndef MCENGINE_ANDROID_HPP
#define MCENGINE_ANDROID_HPP

// 逆天
#include "jni.h"
#include <string>
//等下
namespace android {
    extern JavaVM *jvm;

    JNIEnv* getJNIEnv();
    jobject getApplicationContext(JNIEnv* env);
    void showToast(JNIEnv* env, jstring toast);
    const char* jstringToCharArr(JNIEnv* env, jstring str);
    jstring charArrToJstring(JNIEnv* env, const char* arr);
    JavaVM* getJavaVM();
    void setJavaVM(JavaVM* vm);
    const char * getExternalFilePath(JNIEnv *env, const char *bytes, jobject context);
} // namespace android

#endif //MCENGINE_ANDROID_HPP
