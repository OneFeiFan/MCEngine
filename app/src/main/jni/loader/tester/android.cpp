//
// Created by 30225 on 2023/7/30.
//

#include "android.hpp"

JavaVM *android::jvm = nullptr;

JNIEnv *android::getJNIEnv()
{
    if (jvm != nullptr)
    {
        JNIEnv *env;
        jvm->AttachCurrentThread(&env, NULL);
        if (env != nullptr)
        {
            return env;
        }
    }
    return nullptr;
}

jobject android::getApplicationContext(JNIEnv *env)
{
    // 获取Activity Thread的实例对象
    jclass activityThread = env->FindClass("android/app/ActivityThread");
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread,
            "currentActivityThread",
            "()Landroid/app/ActivityThread;");
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
    // 获取Application，也就是全局的Context
    jmethodID getApplication = env->GetMethodID(activityThread, "getApplication",
            "()Landroid/app/Application;");
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}

// 输出Toast信息
void android::showToast(JNIEnv *env, jstring toast)
{
    jclass jc_Toast = env->FindClass("android/widget/Toast");
    jmethodID jm_makeText = env->GetStaticMethodID(jc_Toast, "makeText",
            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    jobject jo_Toast = env->CallStaticObjectMethod(jc_Toast, jm_makeText,
            getApplicationContext(env), toast, 0);
    jmethodID jm_Show = env->GetMethodID(jc_Toast, "show", "()V");
    env->CallVoidMethod(jo_Toast, jm_Show);
}

const char *android::jstringToCharArr(JNIEnv *env, jstring str)
{
    return env->GetStringUTFChars(str, 0);
}

jstring android::charArrToJstring(JNIEnv *env, const char *arr)
{
    return env->NewStringUTF(arr);
}

JavaVM *android::getJavaVM()
{
    return jvm;
}

void android::setJavaVM(JavaVM *vm)
{
    jvm = vm;
}

const char *android::getExternalFilePath(JNIEnv *env, const char *bytes, jobject context)
{
    // 获取 Context 类
    jclass contextClass = env->GetObjectClass(context);

    // 获取 getExternalFilesDir 方法的 ID
    jmethodID getExternalFilesDirMethodId = env->GetMethodID(contextClass, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");

    // 调用 getExternalFilesDir 方法获取 File 对象
    jstring type = env->NewStringUTF(bytes);

    jobject fileObject = env->CallObjectMethod(context, getExternalFilesDirMethodId, type);
    env->DeleteLocalRef(type);

    // 获取 getAbsolutePath 方法的 ID
    jclass fileClass = env->GetObjectClass(fileObject);

    jmethodID getAbsolutePathMethodId = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");

    // 调用 getAbsolutePath 方法获取路径字符串
    jstring pathString = static_cast<jstring>(env->CallObjectMethod(fileObject, getAbsolutePathMethodId));

    // 将路径字符串转换为 c字符串
    const char *path = env->GetStringUTFChars(pathString, nullptr);

    // 释放资源
    env->ReleaseStringUTFChars(pathString, path);
    env->DeleteLocalRef(fileObject);
    env->DeleteLocalRef(contextClass);

    // 返回结果
    return path;
}
