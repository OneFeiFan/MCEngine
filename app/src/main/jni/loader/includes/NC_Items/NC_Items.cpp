//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "NC_Items.hpp"

std::vector<NC_Items *> normalItemsPoolArray;
std::map<short,Item::Tier *> tiersPool;
NC_Items::NC_Items(const char *name, const char *iconName, int iconData, const CreativeItemCategory type) : name(name), iconName(iconName), iconData(iconData), type(type)
{
    ptr = nullptr;
}

NC_Items* NC_Items::createObj(const char *name, const char *iconName,int iconData, const CreativeItemCategory type)
{
    NC_Items* item = new NC_Items(name, iconName, iconData, type);
    normalItemsPoolArray.emplace_back(item);
    return item;
}



void NC_Items::setItemPtr(Item *ptr_)
{
    ptr = ptr_;
}

const char *NC_Items::getName() const
{
    return name;
}

const char *NC_Items::getIconName() const
{
    return iconName;
}

int NC_Items::getIconData() const
{
    return iconData;
}

Item *NC_Items::getPtr()
{
    return ptr;
}

CreativeItemCategory NC_Items::getType()
{
    return type;
}