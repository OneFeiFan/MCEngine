//
// Created by 30225 on 2023/7/24.
//

#ifndef MCENGINE_NC_ITEMS_HPP
#define MCENGINE_NC_ITEMS_HPP

#include <map>
#include <vector>
#include <jni.h>
#include "../../headers/CreativeItemCategory.h"
#include "../../headers/Fake_Item.hpp"
#include "headers/Other.hpp"

class NC_Items
{
private:
    const char *name;
    const char *iconName;
    const int iconData;
    const CreativeItemCategory type;
    Item *ptr;
public:
    NC_Items(const char *name, const char *iconName, int iconData, CreativeItemCategory type);
    static NC_Items* createObj(const char *name, const char *iconName, int iconData, const CreativeItemCategory type);
    void setItemPtr(Item *ptr);
    const char *getName() const;
    const char *getIconName() const;
    int getIconData() const;
    CreativeItemCategory getType();
    Item *getPtr();
};
extern std::vector<NC_Items *> normalItemsPoolArray;
extern std::map<const char*,Item::Tier *,cmp_str> tiersPool;
#endif //MCENGINE_NC_ITEMS_HPP
