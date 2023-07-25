#include "includes/NCHookFR.h"
#include "JniToNative.hpp"
#include <iostream>
#include <cstring>
#include "headers/NC_items.hpp"
#include "headers/Fake_Actor.hpp"
#include "headers/Fake_BlockSource.hpp"
#include "headers/Fake_BlockLegacy.hpp"
#include "headers/Fake_ItemStackBase.hpp"
#include "headers/Fake_ItemRegistry.hpp"
#include "headers/Fake_Item.hpp"
#include "headers/CreativeItemCategory.h"
class CreativeItemRegistry;

void (*base_Block_onPlace)(void *, BlockSource &, BlockPos const &, Block const &);

void NC_Block_onPlace(void *ptr, BlockSource &blockSource, BlockPos const &pos, Block const &block)
{
    // jclass CLASS = EXHookFR::hookerPtr->Class;
    // invokeCallback(CLASS, "onBlockPlace", "(JJ)V", (jlong)&blockSource, (jlong)&pos);
    return base_Block_onPlace(ptr, blockSource, pos, block);
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
// WeakPtr<Item> (*base_registerItem)(std::string const &, short);
// WeakPtr<Item> EX_registerItem(std::string const &str, short num)
// {

//     return base_registerItem(str, num);
// }
class Experiments;

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

void (*base_Item_setIcon)(void *, std::string const &, short);

void NC_Item_setIcon(void *ptr, std::string const &str, short data)
{
    return base_Item_setIcon(ptr, str, data);
}

// void (*base_Item_setIcon1)(void *, TextureUVCoordinateSet const &);
// void EX_Item_setIcon1(void *ptr, TextureUVCoordinateSet const &a)
// {
//     return base_Item_setIcon1(ptr, a);
// }

// TextureUVCoordinateSet test;
// void (*base_Item_getTextureUVCoordinateSet)(void *, std::string, int);
// void EX_Item_getTextureUVCoordinateSet(void *ptr, std::string str, int a)
// {
//     return base_Item_getTextureUVCoordinateSet(ptr, std::move(str), a);
// }
// TextureUVCoordinateSet const &(*base_Item_getIcon)(Item *, ItemStackBase const &, int, bool);
// TextureUVCoordinateSet const &EX_Item_getIcon(Item *ptr, ItemStackBase const &a, int b, bool c)
// {
//     return base_Item_getIcon(ptr, a, b, c);
// }

// void (*test11)(std::string, std::string, int);
// void test_(std::string str1, std::string str2, int i)
// {
//     return test11(std::move(str1), std::move(str2), i);
// }
void *(*base_VanillaItems_initClientData)(void *, Experiments const &);

void *NC_VanillaItems_initClientData(void *ptr, Experiments const &e)
{
    auto obj = base_VanillaItems_initClientData(ptr, e);

    try{
        for(NC_Items *temp: itemsPoolArray){
            base_Item_setIcon(temp->getPtr(), temp->getIconName(), (short) temp->getIconData());
        }
    }catch(const std::exception &e){
        std::cerr << e.what() << '\n';
    }
    return obj;
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

class ActorInfoRegistry;

class BlockDefinitionGroup;


class BaseGameVersion;

void *(*base_VanillaItems_serverInitCreativeItemsCallback)(void *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, bool, BaseGameVersion const &, Experiments const &);

void *NC_VanillaItems_serverInitCreativeItemsCallback(void *ptr, ActorInfoRegistry *a, BlockDefinitionGroup *b, CreativeItemRegistry *c, bool d, BaseGameVersion const &e, Experiments const &f)
{
    auto obj = base_VanillaItems_serverInitCreativeItemsCallback(ptr, a, b, c, d, e, f);

    for(NC_Items *temp: itemsPoolArray){
        std::cout << 111 << std::endl;
    }
    return obj;
}

void NCHookFR::init()
{
    // fake区
    NC_FakeNative((void **) &fake_Actor_getRegion, "_ZNK5Actor9getRegionEv");
    NC_FakeNative((void **) &fake_Actor_isSneaking, "_ZNK5Actor10isSneakingEv");
    NC_FakeNative((void **) &fake_BlockLegacy_getBlockItemId, "_ZNK11BlockLegacy14getBlockItemIdEv");
    NC_FakeNative((void **) &fake_BlockSource_getBlock, "_ZNK11BlockSource8getBlockEiii");
    NC_FakeNative((void **) &fake_Item_getId, "_ZNK4Item5getIdEv");
    NC_FakeNative((void **) &fake_ItemRegistry_mMaxItemID, "_ZN12ItemRegistry10mMaxItemIDE");
    NC_FakeNative((void **) &fake_ItemRegistry_registerItemShared, "_ZN12ItemRegistry18registerItemSharedI4ItemJRsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEDpOT0_");
    NC_FakeNative((void **) &fake_ItemStackBase_getId, "_ZNK13ItemStackBase5getIdEv");
    NC_FakeNative((void **) &fake_Item_getCommandName, "_ZNK4Item14getCommandNameEv");
    NC_FakeNative((void **) &fake_Item_setCategory, "_ZN4Item11setCategoryE20CreativeItemCategory");
    // hook区
    NC_InLineHook((void *) NC_Block_onPlace, (void **) &base_Block_onPlace, "_ZNK5Block7onPlaceER11BlockSourceRK8BlockPosRKS_");
    NC_InLineHook((void *) NC_Item_useOn, (void **) &base_Item_useOn, "_ZNK4Item5useOnER9ItemStackR5Actoriiihfff");
    //InLineHook((void *) NC_Item_useOn, (void **) &base_Item_useOn, "_ZN12ItemRegistry12registerItemI4ItemJEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEsDpOT0_");
    NC_InLineHook((void *) NC_VanillaItems_registerItems, (void **) &base_VanillaItems_registerItems, "_ZN12VanillaItems13registerItemsERK11Experimentsb");
    NC_InLineHook((void *) NC_VanillaItems_initClientData, (void **) &base_VanillaItems_initClientData, "_ZN12VanillaItems14initClientDataER11Experiments");
    NC_InLineHook((void *) NC_Item_setIcon, (void **) &base_Item_setIcon, "_ZN4Item7setIconERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    //    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item7setIconERK22TextureUVCoordinateSet");
    //    MSHookFunction(ptr, (void *)&EX_Item_setIcon1, (void **)&base_Item_setIcon1);
    // InLineHook((void *)EX_Item_getIcon, (void **)&base_Item_getIcon, "_ZNK4Item7getIconERK13ItemStackBaseib");
    //    ptr = (void *)dlsym(this->MCHandle, "_ZN13ItemStackBaseC2ERK4Itemii");
    //    MSHookFunction(ptr, (void *)&EX_ItemStackBase, (void **)&base_ItemStackBase);
    NC_InLineHook((void *) NC_VanillaItems_serverInitCreativeItemsCallback, (void **) &base_VanillaItems_serverInitCreativeItemsCallback, "_ZN12VanillaItems31serverInitCreativeItemsCallbackEP17ActorInfoRegistryP20BlockDefinitionGroupP20CreativeItemRegistrybRK15BaseGameVersionRK11Experiments");
    NC_InLineHook((void *) NC_Item_addCreativeItem, (void **) &base_Item_addCreativeItem, "_ZN4Item15addCreativeItemEPS_s");
    //    ptr = (void *)dlsym(this->MCHandle, "_ZN22TextureUVCoordinateSetC1Efffftt16ResourceLocationft");
    //    MSHookFunction(ptr, (void *)&EX_TextureUVCoordinateSet_TextureUVCoordinateSet, (void **)&base_TextureUVCoordinateSet_TextureUVCoordinateSet);
    //    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item25getTextureUVCoordinateSetERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    //    MSHookFunction(ptr, (void *)&EX_Item_getTextureUVCoordinateSet, (void **)&base_Item_getTextureUVCoordinateSet);
    //    ptr = (void *)dlsym(this->MCHandle, "_Z15setIconIfLegacyRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEES7_i");
    //    MSHookFunction(ptr, (void *)&test_, (void **)&test11);
}