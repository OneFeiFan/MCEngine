//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/feifan/ItemFaker.hpp"
#include "includes/ItemFactory/ItemFactory.hpp"
#include "headers/feifan/HashedStringFaker.hpp"
#include "headers/feifan/BlockTypeRegistryFaker.hpp"
#include "headers/feifan/ItemRegistryFaker.hpp"
#include "tester/android.hpp"
#include "includes/BlockFactory/BlockFactory.hpp"
#include "IDPool.hpp"

//#include "../includes/json/json.h"
Item::Tier::Tier(int level, int durability, float speed, int damage, int echantmentValue) : mLevel(level), mDurability(durability), mSpeed(speed), mDamage(damage), mEnchantmentValue(echantmentValue){}

bool forBlock;
//fake区
#define def(type, method, args...) type (*fake_##method) (args)

def(short, Item_getId, Item*);
def(char*, Item_getCommandName, Item*);
def(void, Item_setCategory, Item*, CreativeItemCategory);
def(bool, Item_isFood, Item*);
def(void*, Item_addTag, Item*, HashedString*);
def(void, Item_initClient, Item*, Json::Value &, Json::Value &);
def(int, UseAnimationFromString, std::string const&);
def(float, FoodSaturationFromString, std::string const&);
def(int, Tier_getUses, Item::Tier*);
def(int, Tier_getAttackDamageBonus, Item::Tier*);
def(Item*, Item_setMaxDamage, Item*, int);
def(Item*, Item_setMaxStackSize, Item*, unsigned char);
def(Item*, Item_toBlockId, Item*, short);
def(BlockLegacy*, Item_getLegacyBlock, Item*);
def(bool, Item_isSeed, Item*);
def(const char*, Item_getFullItemName, Item*);

//hook区
#define hook(type, method, args...) type (*base_##method) (args)

hook(Item*, Item_Item, Item *, std::string const&, short);
hook(void, Item_setIcon, Item*, std::string const&, short);
hook(void*, Item_addCreativeItem, Item*, short);
hook(void, Item_useOn, Item*, ItemStack*, Actor*, int, int, int, short, float, float, float);
hook(void*, Item_addTag, Item*, HashedString*);
hook(int, Item_initServer, Item*, Json::Value &);
hook(void, Item_initClient, Item*, Json::Value &, Json::Value &);
hook(bool, BlockItem__useOn, Item*, ItemStackBase &, float*, BlockPos const&, uint8_t, float, float, float);
void NC_Item_setIcon(Item *ptr, std::string const &str, short data)
{
    return base_Item_setIcon(ptr, str, data);
}

void *NC_Item_addCreativeItem(Item *obj, short a)
{
    if(forBlock){
        for(auto &NC_BlockPtr: BlockFactory::blocksPoolArray){
            BlockLegacy *blockPtr = fake_BlockTypeRegistry_lookupByName(NC_BlockPtr->getName(), true).get();
            short id = fake_BlockLegacy_getBlockItemId(blockPtr);
            Item *itemPtr = fake_ItemRegistry_getItemById(id).get();
            base_Item_addCreativeItem(itemPtr, 0);
        }
        forBlock = false;
    }
    return base_Item_addCreativeItem(obj, a);
}

bool NC_Item_useOn_first = true;

void NC_Item_useOn(Item *ptr, ItemStack *itemstack, Actor *actor, int x, int y, int z, short face, float vecX, float vecY, float vecZ)
{
    if (NC_Item_useOn_first) {
        //JNIEnv *env = android::getJNIEnv();
        //jmethodID id = env->GetStaticMethodID(NativeClass::ItemCallback, "onItemUse", "(JJJIIISFFF)V");
        //env->CallStaticVoidMethod(NativeClass::ItemCallback, id, (jlong) ptr, (jlong) itemstack, (jlong) actor, x, y, z, face, vecX, vecY, vecZ);
        NC_Item_useOn_first = false;
    } else {
        NC_Item_useOn_first = true;
    }
}

void *NC_Item_addTag(Item *ptr, HashedString *hashedString)
{
    return base_Item_addTag(ptr, hashedString);
}

int NC_Item_initServer(Item *ptr, Json::Value &ptr_)
{
    return base_Item_initServer(ptr, ptr_);
}

void NC_Item_initClient(Item *ptr, Json::Value &ptr_, Json::Value &ptr_1)
{
    base_Item_initClient(ptr, ptr_, ptr_1);
}

bool NC_BlockItem__useOn(Item *ptr, ItemStackBase &a, float *b, BlockPos const &c, uint8_t d, float x, float y, float z)
{
    std::cout << fake_Item_getCommandName(ptr) << std::endl;
    return base_BlockItem__useOn(ptr, a, b, c, d, x, y, z);
}
Item *NC_Item_Item(Item* item, std::string const &name, short id)
{
    return base_Item_Item(item, name, id);
};