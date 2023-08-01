//
// Created by 30225 on 2023/7/24.
//

#ifndef MCENGINE_NC_ITEMS_H
#define MCENGINE_NC_ITEMS_H

#include <map>
#include <vector>
#include "../../headers/CreativeItemCategory.h"
#include "../../headers/Fake_Item.h"

class NC_Items
{
private:
    const char *name;
    const char *iconName;
    const int iconData;
    const bool inCreative;
    const CreativeItemCategory type;
    const char *foodData = nullptr;
    Item *ptr;

public:
    //NC_Items(const char *name, const char *iconName, int iconData, bool inCreative);

    NC_Items(const char *name, const char *iconName, int iconData, bool inCreative, CreativeItemCategory type);

    static NC_Items* createNormalNCIObj(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type);

    static NC_Items* createFoodNCIObj(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type ,const char *foodData);

    //static void createNCIObject(const char *name, const char *iconName, const int iconData, const bool inCreative);
    void setTypeData(const char *);

    const char *getTypeData();

    void setItemPtr(Item *ptr);

    const char *getName() const;

    const char *getIconName() const;

    int getIconData() const;

    bool isInCreative() const;

    CreativeItemCategory getType();

    Item *getPtr();
};

extern std::vector<NC_Items *> normalItemsPoolArray;
//extern std::map<short, NC_Items *> normalItemsPoolMap;

extern std::vector<NC_Items *> foodItemsPoolArray;
//extern std::map<short, NC_Items *> foodItemsPoolMap;
#endif //MCENGINE_NC_ITEMS_H
