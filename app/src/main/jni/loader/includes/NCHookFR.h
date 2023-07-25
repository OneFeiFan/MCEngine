#ifndef NC_HOOKER_FR_H
#define NC_HOOKER_FR_H

#include <jni.h>

static void (*NC_InLineHook)(void *, void *, const char *);
static void (*NC_FakeNative)(void **,const char *);
class NCHookFR
{
private:
    [[maybe_unused]] void *MCHandle;

public:
    static NCHookFR *hookerPtr;
    static JavaVM *jvm;
    [[maybe_unused]] static jclass Class;

public:
    NCHookFR(void *handle);
    void init();
    static JNIEnv *getENV();
};
#endif