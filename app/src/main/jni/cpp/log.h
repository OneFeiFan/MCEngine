//
// Created by 25843 on 2023/7/20.
//

#ifndef MCENGINE_LOG_H
#define MCENGINE_LOG_H

class log {
public:
    static void writeFile();
    static void LogError(char*, std::string);
};
#endif //MCENGINE_LOG_H
