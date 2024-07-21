//
// Created by 30225 on 2023/8/11.
//

#ifndef MCENGINE_SWORDITEMFACTORY_HPP
#define MCENGINE_SWORDITEMFACTORY_HPP


#include "ItemFactory.hpp"

class SwordItemFactory : public ItemFactory
{
private:
    const char *tier;
    int mDurability;
    int mDamage;
public:
    static std::map<const char *,Item::Tier*,cmp_str> tiersPool;
    static std::vector<SwordItemFactory*> swordItemsPoolArray;
    SwordItemFactory(const char *name, const char *iconName, int iconData, const CreativeItemCategory type) : ItemFactory(name, iconName, iconData, type){}
    static SwordItemFactory *createObj(const char *name, const char *iconName, int iconData, const CreativeItemCategory type, const char *tier_, int durability, int damage)
    {
        Item::Tier *ptr = tiersPool[tier_];
        auto *item = new SwordItemFactory(name, iconName, iconData, type);
        item->tier = tier_;
        item->mDurability = durability ? durability : fake_Tier_getUses(ptr);
        item->mDamage = damage ? damage : fake_Tier_getAttackDamageBonus(ptr) + 4;
        swordItemsPoolArray.emplace_back(item);
        IDPool::setMap(name);
        return item;
    }
    const char *getTier() const {
        return tier;
    }
    int getDurability() const {
        return mDurability;
    }
    int getDamage() const {
        return mDamage;
    }

};

#endif //MCENGINE_SWORDITEMFACTORY_HPP
