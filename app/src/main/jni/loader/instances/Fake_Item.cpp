//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/Fake_Item.hpp"
#include "NC_Items.hpp"
#include "headers/Fake_HashedString.h"
#include "headers/Fake_BlockTypeRegistry.hpp"
#include "headers/Fake_ItemRegistry.hpp"

//#include "../includes/json/json.h"
Item::Tier::Tier(int level, int durability, float speed, int damage, int echantmentValue) : mLevel(level), mDurability(durability), mSpeed(speed), mDamage(damage), mEnchantmentValue(echantmentValue){}

//fake区
short (*fake_Item_getId)(Item *);

char *(*fake_Item_getCommandName)(Item *);

void (*fake_Item_setCategory)(Item *, CreativeItemCategory);

bool (*fake_Item_isFood)(Item *);

void *(*fake_Item_addTag)(Item *, HashedString *);

void (*fake_Item_initClient)(Item *, Json::Value &, Json::Value &);

int (*fake_UseAnimationFromString)(std::string const &);

float (*fake_FoodSaturationFromString)(std::string const &);

int (*fake_Tier_getUses)(Item::Tier *);

int (*fake_Tier_getAttackDamageBonus)(Item::Tier *);

Item *(*fake_Item_setMaxDamage)(Item *, int);

Item *(*fake_Item_setMaxStackSize)(Item *, unsigned char);

Item *(*fake_Item_toBlockId)(Item *, short);

BlockLegacy *(*fake_Item_getLegacyBlock)(Item *);

//hook区
void (*base_Item_setIcon)(Item *, std::string const &, short);

void NC_Item_setIcon(Item *ptr, std::string const &str, short data)
{
    return base_Item_setIcon(ptr, str, data);
}

bool forBlock = true;

void *(*base_Item_addCreativeItem)(Item *, short);

void *NC_Item_addCreativeItem(Item *obj, short a)
{
    if(forBlock){
        BlockLegacy *tempBlock1 = fake_BlockTypeRegistry_lookupByName("block_Temp", true).get();
        short id = fake_BlockLegacy_getBlockItemId(tempBlock1);
        Item *testitem = fake_ItemRegistry_getItemById(id).get();
        base_Item_addCreativeItem(testitem, fake_Item_getId(testitem));
        forBlock = false;
    }
    return base_Item_addCreativeItem(obj, a);
}

void (*base_Item_useOn)(Item *, ItemStack &, Actor &, int, int, int, unsigned char, float, float, float);

void NC_Item_useOn(Item *ptr, ItemStack &itemstack, Actor &actor, int x, int y, int z, unsigned char d, float e, float f, float g)
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
    //std::cout << fake_Item_isFood(ptr) << std::endl;
    return base_Item_useOn(ptr, itemstack, actor, x, y, z, d, e, f, g);
}

void *(*base_Item_addTag)(Item *, HashedString *);

[[maybe_unused]] void *NC_Item_addTag(Item *ptr, HashedString *hashedString)
{
    return base_Item_addTag(ptr, hashedString);
}

int (*base_Item_initServer)(Item *, Json::Value &);

int NC_Item_initServer(Item *ptr, Json::Value &ptr_)
{
    //ptr_[""];
    //std::cout<<ptr_.type()<<std::endl;
    base_Item_initServer(ptr, ptr_);
    return 1;
}

void (*base_Item_initClient)(Item *, Json::Value &, Json::Value &);

void NC_Item_initClient(Item *ptr, Json::Value &ptr_, Json::Value &ptr_1)
{
    base_Item_initClient(ptr, ptr_, ptr_1);
}

bool (*base_BlockItem__useOn)(Item *, ItemStackBase &, float *, BlockPos const &, uint8_t, float, float, float);

bool NC_BlockItem__useOn(Item *ptr, ItemStackBase &a, float *b, BlockPos const &c, uint8_t d, float x, float y, float z)
{

    std::cout << fake_Item_getCommandName(ptr) << std::endl;
    return base_BlockItem__useOn(ptr, a, b, c, d, x, y, z);
}