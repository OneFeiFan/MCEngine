//
// Created by 30225 on 2023/8/11.
//

#ifndef MCENGINE_NC_SWORDITEMS_HPP
#define MCENGINE_NC_SWORDITEMS_HPP


#include "NC_Items.hpp"

class NC_SwordItems : public NC_Items
{
private:
    int tier;
    int mDurability;
    int mDamage;
public:
    NC_SwordItems(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type);

    static NC_SwordItems *createObj(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type, int tier_, int durability, int damage);

    int getTier() const;

    int getDurability() const;

    int getDamage() const;

};

extern std::vector<NC_SwordItems *> swordItemsPoolArray;
#endif //MCENGINE_NC_SWORDITEMS_HPP
