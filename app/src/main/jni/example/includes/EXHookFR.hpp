#ifndef EX_HOOKER_FR_HPP
#define EX_HOOKER_FR_HPP

#include <jni.h>
class EXHookFR
{
private:
    void *MCHandle;

public:
    static EXHookFR *hookerPtr;
    static JavaVM *jvm;
    static jclass Class;
public:
    EXHookFR(void *handle);
    void init();
    JNIEnv *getENV();
};
#endif