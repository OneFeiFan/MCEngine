//
// Created by 30225 on 2023/8/11.
//

#include "NC_SwordItems.hpp"

std::vector<NC_SwordItems *> swordItemsPoolArray;

NC_SwordItems::NC_SwordItems(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type) : NC_Items(name, iconName, iconData, inCreative, type){}

NC_SwordItems *NC_SwordItems::createObj(const char *name, const char *iconName, int iconData, bool inCreative, const CreativeItemCategory type, short tier_, int durability, int damage)
{
    Item::Tier *ptr = tiersPool[tier_];
    auto *item = new NC_SwordItems(name, iconName, iconData, inCreative, type);
    item->tier = tier_;
    item->mDurability = durability ? durability : fake_Tier_getUses(ptr);
    item->mDamage = damage ? damage : fake_Tier_getAttackDamageBonus(ptr) + 4;
    swordItemsPoolArray.emplace_back(item);
    return item;
}

short NC_SwordItems::getTier() const
{
    return tier;
}

int NC_SwordItems::getDurability() const
{
    return mDurability;
}

int NC_SwordItems::getDamage() const
{
    return mDamage;
}
