#ifndef _JAVAATACH_H
#define _JAVAATACH_H

class JavaAtach {
public:
    static JavaVM* jvm;
    static JNIEnv* attach();
    static void init(JavaVM* vm);
};
#endif