//
// Created by 30225 on 2023/8/11.
//

#ifndef MCENGINE_NC_FOODITEMS_HPP
#define MCENGINE_NC_FOODITEMS_HPP


#include "NC_Items.hpp"

class NC_FoodItems : public NC_Items
{
private:
    const char *foodData = nullptr;
public:
    NC_FoodItems(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type);

    static NC_FoodItems* createObj(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type ,const char *data);

    const char *getTypeData();

};

extern std::vector<NC_FoodItems *> foodItemsPoolArray;
#endif //MCENGINE_NC_FOODITEMS_HPP
