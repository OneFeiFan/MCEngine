#pragma once
#ifndef EX_FAKE_ITEM_HPP
#define EX_FAKE_ITEM_HPP

#include <stdint.h>
#include <dlfcn.h>
#include "../mojang/CreativeItemCategory.h"
#include "../mojang/Item.h"
#include "Json_ValueFaker.hpp"
#include "BlockLegacyFaker.hpp"
#include "ItemStackBaseFaker.hpp"

// This header template file is generated by Disassembler.

class BlockItem : public Item{};
class BlockPos;
extern bool forBlock;
// fake区域
#define Extern(type, method, args...) extern type (*fake_##method) (args)
Extern(short, Item_getId, Item*);
Extern(char*, Item_getCommandName, Item*);
Extern(void, Item_setCategory, Item*, CreativeItemCategory);
Extern(bool, Item_isFood, Item*);
Extern(void*, Item_addTag, Item*, HashedString*);
Extern(void, Item_initClient, Item*, Json::Value&, Json::Value&);
Extern(int, UseAnimationFromString, std::string const&);
Extern(float, FoodSaturationFromString, std::string const&);
Extern(int, Tier_getUses, Item::Tier*);
Extern(int, Tier_getAttackDamageBonus, Item::Tier*);
Extern(Item*, Item_setMaxDamage, Item*, int);
Extern(Item*, Item_setMaxStackSize, Item*, unsigned char);
Extern(Item*, Item_toBlockId, Item*, short);
Extern(BlockLegacy*, Item_getLegacyBlock, Item*);
Extern(bool, Item_isSeed, Item*);
Extern(const char*, Item_getFullItemName, Item*);

//_ZNK4Item14getLegacyBlockEv
//hook区
#define Extern(type, method, args...) extern type (*base_##method) (args)
Extern(Item*, Item_Item, Item*, std::string const&, short);
Extern(void, Item_setIcon, Item*, std::string const&, short);
Extern(void*, Item_addCreativeItem, Item*, short);
Extern(void, Item_useOn, Item*, ItemStack*, Actor*, int, int, int, short, float, float, float);
Extern(void*, Item_addTag, Item*, HashedString*);
Extern(int, Item_initServer, Item*, Json::Value&);
Extern(void, Item_initClient, Item*, Json::Value&, Json::Value&);
Extern(bool, BlockItem__useOn, Item*, ItemStackBase&, float*, BlockPos const&, uint8_t, float, float, float);
Extern(bool, Item_isSeed, Item*);

#define Extern(type, method, args...) extern type method (args)
Extern(Item*, NC_Item_Item, Item*, std::string const&, short);
Extern(void, NC_Item_setIcon, Item*, std::string const&, short);
Extern(void*, NC_Item_addCreativeItem, Item*, short);
Extern(void, NC_Item_useOn, Item*, ItemStack*, Actor*, int, int, int, short, float, float, float);
Extern(void*, NC_Item_addTag, Item*, HashedString*);
Extern(int, NC_Item_initServer, Item*, Json::Value&);
Extern(void, NC_Item_initClient, Item*, Json::Value&, Json::Value&);
Extern(bool, NC_BlockItem__useOn, Item*, ItemStackBase&, float*, BlockPos const&, uint8_t, float, float, float);
//_ZNK9BlockItem6_useOnER9ItemStackR5Actor8BlockPoshfff
//
#endif