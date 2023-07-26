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
    const CreativeItemCategory type = CreativeItemCategory::Construction;
    Item *ptr;

public:
    NC_Items(const char *name, const char *iconName, int iconData, bool inCreative);

    NC_Items(const char *name, const char *iconName, int iconData, bool inCreative, CreativeItemCategory type);

    static void createNCIObject(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type);

    static void createNCIObject(const char *name, const char *iconName, const int iconData, const bool inCreative);

    void setItemPtr(Item *ptr);

    const char *getName() const;

    const char *getIconName() const;

    int getIconData() const;

    bool isInCreative() const;

    CreativeItemCategory getType();

    Item *getPtr();
};
extern std::vector<NC_Items *> itemsPoolArray;
extern std::map<short, NC_Items *> itemsPoolMap;


#endif //MCENGINE_NC_ITEMS_H
