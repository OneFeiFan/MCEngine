//
// Created by 30225 on 2023/7/24.
//
#include "NC_items.hpp"
#include <iostream>

NC_Items::NC_Items(const char *name, const char *iconName, const int iconData, const bool inCreative) : name(name), iconName(iconName), iconData(iconData), inCreative(inCreative)
{
    this->ptr = nullptr;
}

NC_Items::NC_Items(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type) : name(name), iconName(iconName), iconData(iconData), inCreative(inCreative), type(type)
{
    this->ptr = nullptr;
}

void NC_Items::createNCIObject(const char *name, const char *iconName, const int iconData, const bool inCreative)
{
    itemsPoolArray.push_back(new NC_Items(name,iconName,iconData,inCreative));
}

void NC_Items::createNCIObject(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type)
{
    itemsPoolArray.push_back(new NC_Items(name,iconName,iconData,inCreative,type));
}

void NC_Items::setItemPtr(Item *ptr_)
{
    this->ptr = ptr_;
}

const char *NC_Items::getName() const
{
    return this->name;
}

const char *NC_Items::getIconName() const
{
    return this->iconName;
}

int NC_Items::getIconData() const
{
    return this->iconData;
}

bool NC_Items::isInCreative() const
{
    return this->inCreative;
}

Item *NC_Items::getPtr()
{
    return this->ptr;
}

CreativeItemCategory NC_Items::getType()
{
    return this->type;
}
