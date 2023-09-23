//
// Created by 30225 on 2023/8/11.
//

#ifndef MCENGINE_NC_SWORDITEMS_HPP
#define MCENGINE_NC_SWORDITEMS_HPP


#include "NC_Items.hpp"

class NC_SwordItems : public NC_Items
{
private:
    const char *tier;
    int mDurability;
    int mDamage;
public:
    NC_SwordItems(const char *, const char *, int, const CreativeItemCategory);

    static NC_SwordItems *createObj(const char *, const char *, int, const CreativeItemCategory, const char *, int, int);

    const char *getTier() const;

    int getDurability() const;

    int getDamage() const;

};

extern std::vector<NC_SwordItems *> swordItemsPoolArray;
#endif //MCENGINE_NC_SWORDITEMS_HPP
