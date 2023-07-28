//
// Created by 30225 on 2023/7/26.
//
#include "NC_items.h"

std::vector<NC_Items *> normalItemsPoolArray;
std::map<short, NC_Items *> normalItemsPoolMap;

std::vector<NC_Items *> foodItemsPoolArray;
std::map<short, NC_Items *> foodItemsPoolMap;
//NC_Items::NC_Items(const char *name, const char *iconName, const int iconData, const bool inCreative) : name(name), iconName(iconName), iconData(iconData), inCreative(inCreative)
//{
//    this->ptr = nullptr;
//}

NC_Items::NC_Items(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type) : name(name), iconName(iconName), iconData(iconData), inCreative(inCreative), type(type)
{
    this->ptr = nullptr;
}

//void NC_Items::createNCIObject(const char *name, const char *iconName, const int iconData, const bool inCreative)
//{
//    itemsPoolArray.push_back(new NC_Items(name,iconName,iconData,inCreative));
//}

void NC_Items::createNormalNCIObj(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type)
{
    normalItemsPoolArray.emplace_back(new NC_Items(name, iconName, iconData, inCreative, type));
}

void NC_Items::createFoodNCIObj(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type, const char *foodData)
{
    foodItemsPoolArray.emplace_back(new NC_Items(name, iconName, iconData, inCreative, type));
    foodItemsPoolArray.back()->setTypeData(foodData);
}

void NC_Items::setTypeData(const char *data)
{
    this->foodData = data;
}

const char *NC_Items::getTypeData()
{
    return this->foodData;
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