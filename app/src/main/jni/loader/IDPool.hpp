//
// Created by 25843 on 2023/10/12.
//

#ifndef MCENGINE_IDPOOL_HPP
#define MCENGINE_IDPOOL_HPP


#include <string>
#include <vector>
#include <map>

class IDPool
{
public:
    static short ItemIdMax;
    static void define(short);
    static std::map<std::string, short&> ItemIdPair;
    static void setMap(const std::string&);
    static short getId(const std::string&);
};


#endif //MCENGINE_IDPOOL_HPP
