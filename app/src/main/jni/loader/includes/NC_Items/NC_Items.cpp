//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "NC_Items.hpp"
#include "tester/android.hpp"
#include "IDPool.hpp"

#define return(i) {return i;}

std::vector<NC_Items *> normalItemsPoolArray;
std::map<const char *,Item::Tier *,cmp_str> tiersPool;

NC_Items::NC_Items(const char *name, const char *iconName, int iconData, const CreativeItemCategory type) : name(name), iconName(iconName), iconData(iconData), type(type)
{
    ptr = nullptr;
}

NC_Items* NC_Items::createObj(const char *name, const char *iconName,int iconData, const CreativeItemCategory type)
{
    auto* item = new NC_Items(name, iconName, iconData, type);
    normalItemsPoolArray.emplace_back(item);
    IDPool::setMap(name);
    return item;
}

void NC_Items::setItemPtr(Item *ptr_)
{
    ptr = ptr_;
}

const char *NC_Items::getName() const return(name);
const char *NC_Items::getIconName() const return(iconName);
int NC_Items::getIconData() const return(iconData);
Item *NC_Items::getPtr() return(ptr);
CreativeItemCategory NC_Items::getType() return(type);