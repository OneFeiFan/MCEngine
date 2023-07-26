//
// Created by 30225 on 2023/7/26.
//
#include "../headers/Fake_Item.h"
#include "NC_items.h"

//fake区
short (*fake_Item_getId)(Item *);

const char *(*fake_Item_getCommandName)(Item *);

void (*fake_Item_setCategory)(Item *, CreativeItemCategory);

//hook区
void (*base_Item_setIcon)(void *, std::string const &, short);

void NC_Item_setIcon(void *ptr, std::string const &str, short data)
{
    return base_Item_setIcon(ptr, str, data);
}

void *(*base_Item_addCreativeItem)(Item *, short);

void *NC_Item_addCreativeItem(Item *obj, short a)
{
    short id = fake_Item_getId(obj);
    if(itemsPoolMap.count(id)){
        if(itemsPoolMap[id]->isInCreative()){
            return base_Item_addCreativeItem(obj, 0);
        }
        return nullptr;
    }
    return base_Item_addCreativeItem(obj, a);
}

void (*base_Item_useOn)(void *, ItemStack &, Actor &, int, int, int, unsigned char, float, float, float);

void NC_Item_useOn(void *ptr, ItemStack &itemstack, Actor &actor, int x, int y, int z, unsigned char d, float e, float f, float g)
{
    // jclass CLASS = EXHookFR::hookerPtr->Class;
    // BlockSource *Region = (BlockSource *)fake_Actor_getRegion(&actor);
    // Block *block = Fake_BlockSource_getBlock(Region, x, y, z);
    // int id = fake_BlockLegacy_getBlockItemId(((BlockLegacy *)*((uint32_t *)block + 2)));
    // if (std::find(barrelIDPool.begin(), barrelIDPool.end(), id) != barrelIDPool.end() && !fake_Actor_isSneaking(&actor))
    // {
    //     if (std::find(forbiddenIDPool.begin(), forbiddenIDPool.end(), fake_ItemStackBase_getId((ItemStackBase *)&itemstack)) != forbiddenIDPool.end())
    //     {
    //         return;
    //     }
    // }
    return base_Item_useOn(ptr, itemstack, actor, x, y, z, d, e, f, g);
}