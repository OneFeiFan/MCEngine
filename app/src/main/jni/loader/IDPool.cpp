//
// Created by 25843 on 2023/10/12.
//

#include <iostream>
#include "IDPool.hpp"
#include "headers/feifan/ItemRegistryFaker.hpp"

short IDPool::ItemIdMax = 0;
std::map<std::string, short&> IDPool::ItemIdPair;
void IDPool::setMap(const std::string& name)
{
    IDPool::ItemIdPair.insert(std::pair<std::string, short&>(name, ++IDPool::ItemIdMax));
}

short IDPool::getId(const std::string& name)
{
    auto index = IDPool::ItemIdPair.find(name);
    if (index == IDPool::ItemIdPair.end()) {
        return 0;
    } else {
        return index->second;
    }
}

void IDPool::define(short id)
{
    IDPool::ItemIdMax = id;//*fake_ItemRegistry_mMaxItemID
}
