//
// Created by 30225 on 2023/7/30.
//

#ifndef MCENGINE_LOG_HPP
#define MCENGINE_LOG_HPP


#include <jni.h>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();

    void log(const std::string& message);
    static Logger* instance;

private:
    std::string filename;
    FILE* file;
};


#endif //MCENGINE_LOG_HPP
