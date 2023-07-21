#ifndef _NATIVEENGINE_H
#define _NATIVEENGINE_H
#include <stdarg.h>
//#include "stl/string"
#include <c++/v1/string>
#include <jni.h>

class NativeEngine {
public:
    static jclass HookEngineptr;
    static jclass HookEngineClass();
    static void HookEngineClass(JNIEnv* env);
/*    static void Log(std::string claz, int a);
    static void Log(std::string claz, float a);
    static void Log(std::string claz, long a);
    static void Log(std::string claz, std::string a);*/
};
#endif