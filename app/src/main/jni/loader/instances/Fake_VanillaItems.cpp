//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/Fake_VanillaItems.h"
#include "../headers/Fake_Item.h"
#include "../headers/Fake_ItemRegistry.h"
#include "NC_items.h"

class Experiments;
//hook区
void *(*base_VanillaItems_registerItems)(void *, Experiments const &, bool);

void *NC_VanillaItems_registerItems(void *ptr, Experiments const &e, bool b)
{
    printf("base_VanillaItems_registerItems\n");
    //log::Toast("注册物品");
    Item *temp;
    for(auto &i: itemsPoolArray){
        temp = fake_ItemRegistry_registerItemShared(i->getName(), (short &) (++fake_ItemRegistry_mMaxItemID)).get();
        i->setItemPtr(temp);
        itemsPoolMap.insert(std::pair<short &, NC_Items *>((short &) fake_ItemRegistry_mMaxItemID, i));
        fake_Item_setCategory(temp, i->getType());
    }

    return base_VanillaItems_registerItems(ptr, e, b);
}

void *(*base_VanillaItems_initClientData)(void *, Experiments const &);

void *NC_VanillaItems_initClientData(void *ptr, Experiments const &e)
{
    try{
        for(NC_Items *temp: itemsPoolArray){
            base_Item_setIcon(temp->getPtr(), temp->getIconName(), (short) temp->getIconData());
        }
    }catch(const std::exception &e){
        std::cerr << e.what() << '\n';
    }
    return base_VanillaItems_initClientData(ptr, e);
}
void *(*base_VanillaItems_serverInitCreativeItemsCallback)(void *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, bool, BaseGameVersion const &, Experiments const &);

void *NC_VanillaItems_serverInitCreativeItemsCallback(void *ptr, ActorInfoRegistry *a, BlockDefinitionGroup *b, CreativeItemRegistry *c, bool d, BaseGameVersion const &e, Experiments const &f)
{
    auto obj = base_VanillaItems_serverInitCreativeItemsCallback(ptr, a, b, c, d, e, f);

    for(NC_Items *temp: itemsPoolArray){
        std::cout << 111 << std::endl;
    }
    return obj;
}