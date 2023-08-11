//
// Created by 30225 on 2023/8/11.
//

#include "NC_FoodItems.hpp"

std::vector<NC_FoodItems *> foodItemsPoolArray;
NC_FoodItems::NC_FoodItems(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type) : NC_Items(name,iconName,iconData,inCreative,type){}

NC_FoodItems* NC_FoodItems::createObj(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type, const char *data)
{
    NC_FoodItems* item = new NC_FoodItems(name, iconName, iconData, inCreative, type);
    item->foodData = data;
    foodItemsPoolArray.emplace_back(item);
    return item;
}


const char *NC_FoodItems::getTypeData()
{
    return this->foodData;
}