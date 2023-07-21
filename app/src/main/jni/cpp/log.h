//
// Created by 25843 on 2023/7/20.
//

#ifndef MCENGINE_LOG_H
#define MCENGINE_LOG_H

#include <jni.h>

class log {
public:
    static void writeFile();
    static void LogError(char*, std::string);
    static std::string JStringTransfer(jstring jStr);
    static char* jstringToChar(jstring jstr);
    static void Toast(std::string);
};
#endif
