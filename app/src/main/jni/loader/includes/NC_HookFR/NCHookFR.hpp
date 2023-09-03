#ifndef NC_HOOKER_FR_H
#define NC_HOOKER_FR_H

#include <jni.h>

extern void NC_InLineHook(void *, void **, const char *);
extern void NC_FakeNative(void **,const char *);
class NCHookFR
{
public:
    static NCHookFR *hookerPtr;
    static JavaVM *jvm;
    [[maybe_unused]] static jclass Class;

public:
    NCHookFR();
    static void init();
    static JNIEnv *getENV();
};
#endif