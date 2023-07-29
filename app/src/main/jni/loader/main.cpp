#include "includes/NC_HookFR/NCHookFR.h"
#include "JniToNative.hpp"
#include <iostream>
#include <cstring>
#include "includes/NC_Items/NC_items.h"
#include "headers/Fake_Actor.hpp"
#include "headers/Fake_BlockSource.hpp"
#include "headers/Fake_BlockLegacy.hpp"
#include "headers/Fake_ItemStackBase.hpp"
#include "headers/Fake_ItemRegistry.h"
#include "headers/Fake_Item.h"
#include "headers/CreativeItemCategory.h"
#include "headers/Fake_VanillaItems.h"
#include "headers/Fake_HashedString.h"
#include "headers/Fake_Json_Value.h"
#include "headers/fake_FoodItemComponentLegacy.h"

class CreativeItemRegistry;

void (*base_Block_onPlace)(void *, BlockSource &, BlockPos const &, Block const &);

void NC_Block_onPlace(void *ptr, BlockSource &blockSource, BlockPos const &pos, Block const &block)
{
    // jclass CLASS = EXHookFR::hookerPtr->Class;
    // invokeCallback(CLASS, "onBlockPlace", "(JJ)V", (jlong)&blockSource, (jlong)&pos);
    return base_Block_onPlace(ptr, blockSource, pos, block);
}


// WeakPtr<Item> (*base_registerItem)(std::string const &, short);
// WeakPtr<Item> EX_registerItem(std::string const &str, short num)
// {

//     return base_registerItem(str, num);
// }




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
    NC_FakeNative((void **) &fake_HashedString_c_str, "_ZNK12HashedString5c_strEv");
    NC_FakeNative((void **) &fake_HashedString_HashedString, "_ZN12HashedStringC2EPKc");
    NC_FakeNative((void **) &fake_Item_isFood, "_ZNK4Item6isFoodEv");
    NC_FakeNative((void **) &fake_Item_addTag, "_ZN4Item6addTagERK12HashedString");
    NC_FakeNative((void **) &fake_Json_Value_size, "_ZNK4Json5Value4sizeEv");
    NC_FakeNative((void **) &fake_Json_Value_asCString, "_ZNK4Json5Value9asCStringEv");
    NC_FakeNative((void **) &fake_Json_Value_getMemberNames, "_ZNK4Json5Value14getMemberNamesEv");
    NC_FakeNative((void **) &fake_Json_Value_resolveReference, "_ZN4Json5Value16resolveReferenceEPKcb");
    NC_FakeNative((void **) &fake_Json_Value_toStyledString, "_ZNK4Json5Value14toStyledStringEv");
    NC_FakeNative((void **) &fake_Item_initClient, "_ZN4Item10initClientERN4Json5ValueES2_");
    NC_FakeNative((void **) &fake_FoodSaturationFromString, "_Z24FoodSaturationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE");
    NC_FakeNative((void **) &fake_UseAnimationFromString, "_Z22UseAnimationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE");
    //NC_FakeNative((void **) &fake_FoodItemComponentLegacy, "_ZN23FoodItemComponentLegacyC2ER4Item");


//
    // hook区
    NC_InLineHook((void *) NC_Block_onPlace, (void **) &base_Block_onPlace, "_ZNK5Block7onPlaceER11BlockSourceRK8BlockPosRKS_");
    NC_InLineHook((void *) NC_Item_useOn, (void **) &base_Item_useOn, "_ZNK4Item5useOnER9ItemStackR5Actoriiihfff");
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
    //NC_InLineHook((void *) NC_Item_addTag, (void **) &base_Item_addTag, "_ZN4Item6addTagERK12HashedString");//大概没大用
    NC_InLineHook((void *) NC_Item_initServer, (void **) &base_Item_initServer, "_ZN4Item10initServerERN4Json5ValueE");
    //NC_InLineHook((void *) NC_Json_Value_Value, (void **) &base_Json_Value_Value, "_ZN4Json5ValueC1EPKcS2_");//这个方法不调用
    //NC_InLineHook((void *) NC_Item_initClient, (void **) &base_Item_initClient, "_ZN4Item10initClientERN4Json5ValueES2_");//无用

    //    ptr = (void *)dlsym(this->MCHandle, "_ZN22TextureUVCoordinateSetC1Efffftt16ResourceLocationft");
    //    MSHookFunction(ptr, (void *)&EX_TextureUVCoordinateSet_TextureUVCoordinateSet, (void **)&base_TextureUVCoordinateSet_TextureUVCoordinateSet);
    //    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item25getTextureUVCoordinateSetERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    //    MSHookFunction(ptr, (void *)&EX_Item_getTextureUVCoordinateSet, (void **)&base_Item_getTextureUVCoordinateSet);
    //    ptr = (void *)dlsym(this->MCHandle, "_Z15setIconIfLegacyRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEES7_i");
    //    MSHookFunction(ptr, (void *)&test_, (void **)&test11);
}