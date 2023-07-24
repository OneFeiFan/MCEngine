#ifndef EX_HOOKER_FR_H
#define EX_HOOKER_FR_H

#include <jni.h>
inline void *(*my_DobbySymbolResolver)(const char *image_name, const char *symbol_name);
inline int (*my_DobbyHook)(void *, void *, void *);
void InLineHook(void *hook, void *original, const char *symbol_name);
void FakeNative(void **fake_fun,const char *symbol_name);
class EXHookFR
{
private:
    [[maybe_unused]] void *MCHandle;

public:
    static EXHookFR *hookerPtr;
    static JavaVM *jvm;
    [[maybe_unused]] static jclass Class;

public:
    EXHookFR(void *handle);
    void init();
    static JNIEnv *getENV();
};
#endif