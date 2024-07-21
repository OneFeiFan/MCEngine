//
// Created by 30225 on 2023/7/30.
//

#include <jni.h>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>

class Logger {
public:
    Logger(const std::string& filename): filename(filename) {
        file = fopen(filename.c_str(), "a");
    };
    ~Logger(){
        if (file != NULL) {
            fclose(file);
        }
    };

    void log(const std::string& message){
        std::time_t now = std::time(nullptr);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

        if (file != NULL) {
            fprintf(file, "[%s] %s\n", timestamp, message.c_str());
            fflush(file);
        }
    };
    static Logger* instance;

private:
    std::string filename;
    FILE* file;
};

Logger* Logger::instance = nullptr;