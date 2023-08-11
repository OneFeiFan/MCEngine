//
// Created by 30225 on 2023/7/24.
//

#ifndef MCENGINE_NC_ITEMS_HPP
#define MCENGINE_NC_ITEMS_HPP

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
    Item *ptr;

public:

    NC_Items(const char *name, const char *iconName, int iconData, bool inCreative, CreativeItemCategory type);

    static NC_Items* createObj(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type);

    void setItemPtr(Item *ptr);

    const char *getName() const;

    const char *getIconName() const;

    int getIconData() const;

    bool isInCreative() const;

    CreativeItemCategory getType();

    Item *getPtr();
};
extern std::vector<NC_Items *> normalItemsPoolArray;
extern std::map<short,Item::Tier *> tiersPool;
#endif //MCENGINE_NC_ITEMS_HPP
