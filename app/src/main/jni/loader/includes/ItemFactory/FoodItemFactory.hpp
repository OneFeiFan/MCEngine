//
// Created by 30225 on 2023/8/11.
//

#ifndef MCENGINE_FOODITEMFACTORY_HPP
#define MCENGINE_FOODITEMFACTORY_HPP


#include "ItemFactory.hpp"

class FoodItemFactory : public ItemFactory
{
private:
    const char *foodData = nullptr;
public:
    FoodItemFactory(const char *name, const char *iconName, int iconData, const CreativeItemCategory type) : ItemFactory(name,iconName,iconData,type){}
    static std::vector<FoodItemFactory*> foodItemsPoolArray;
    static FoodItemFactory* createObj(const char *name, const char *iconName, int iconData, const CreativeItemCategory type, const char *data)
    {
        FoodItemFactory* item = new FoodItemFactory(name, iconName, iconData, type);
        item->foodData = data;
        foodItemsPoolArray.emplace_back(item);
        IDPool::setMap(name);
        return item;
    }
    const char *getTypeData()
    {
        return this->foodData;
    }

};

#endif //MCENGINE_FOODITEMFACTORY_HPP
