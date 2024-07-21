#pragma once
_Pragma("once")
#ifndef HOOKFACTORY_HPP
#define HOOKFACTORY_HPP

#include <jni.h>
#include <cstdio>
#include <iostream>

#include "includes/dobby.h"
#include "includes/ItemFactory/ItemFactory.hpp"
#include "headers/feifan/ActorFaker.hpp"
#include "headers/feifan/BlockSourceFaker.hpp"
#include "headers/feifan/BlockLegacyFaker.hpp"
#include "headers/feifan/ItemStackBaseFaker.hpp"
#include "headers/feifan/ItemRegistryFaker.hpp"
#include "headers/feifan/ItemFaker.hpp"
#include "headers/mojang/CreativeItemCategory.h"
#include "headers/feifan/VanillaItemsFaker.hpp"
#include "headers/feifan/HashedStringFaker.hpp"
#include "headers/feifan/Json_ValueFaker.hpp"
#include "headers/feifan/FoodItemComponentLegacyFaker.hpp"
#include "headers/feifan/VanillaBlockTypesFaker.hpp"
#include "headers/feifan/MaterialFaker.hpp"
#include "headers/feifan/BlockTypeRegistryFaker.hpp"
#include "headers/feifan/BlockGraphicsFaker.hpp"
#include "headers/feifan/Other.hpp"
#include "headers/feifan/BlockFaker.hpp"
#include "headers/feifan/ItemInstanceFaker.hpp"
#include "SwordItemFactory.hpp"

namespace HookFactory
{
    static JavaVM *jvm;
    static jclass Class;
    static void init();
    static JNIEnv *getENV() {
        JNIEnv *env = nullptr;
        int attachStatus = HookFactory::jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
        if (attachStatus == JNI_EDETACHED)
        {
            HookFactory::jvm->AttachCurrentThread(&env, nullptr);
        }
        return env;
    };
    static void InLineHook(void *hook, void **original, const char *symbol_name) {
        void *ptr = DobbySymbolResolver("libminecraftpe.so", symbol_name);
        if (ptr != nullptr) {
            printf("成功获取符号：%s的地址\n", symbol_name);
            if (DobbyHook(ptr, hook, original) == 0) {
                printf("hook成功\n");
            } else {
                printf("hook失败\n");
            }
        } else {
            printf("无法获取符号：%s的地址\n", symbol_name);
        }
    }
    static void FakeNative(void **fake_fun, const char *symbol_name) {
        if (fake_fun) {
            void *symbol = DobbySymbolResolver("libminecraftpe.so", symbol_name);
            if (symbol != nullptr) {
                printf("成功获取符号：%s的地址\n", symbol_name);
                *fake_fun = symbol;
                printf("fake成功\n");
            } else {
                printf("未能获取符号：%s的地址\n", symbol_name);
                printf("fake失败\n");
            }
        }
    }
};

void HookFactory::init()
{
    // fake区
    //实体/玩家？信息类
    FakeNative((void **) &fake_Actor_getRegion, "_ZNK5Actor9getRegionEv");
    FakeNative((void **) &fake_Actor_isSneaking, "_ZNK5Actor10isSneakingEv");
    //Legacy方块类
    FakeNative((void **) &fake_BlockLegacy_getBlockItemId, "_ZNK11BlockLegacy14getBlockItemIdEv");
    FakeNative((void **) &fake_BlockLegacy_createWeakPtr, "_ZN11BlockLegacy13createWeakPtrEv");
    FakeNative((void **) &fake_BlockLegacy_setCategory, "_ZN11BlockLegacy11setCategoryE20CreativeItemCategory");
    FakeNative((void **) &fake_BlockLegacy_setDestroyTime, "_ZN11BlockLegacy14setDestroyTimeEf");
    FakeNative((void **) &fake_BlockLegacy_setExplodeable, "_ZN11BlockLegacy14setExplodeableEf");
    FakeNative((void **) &fake_BlockLegacy_getCommandName, "_ZNK11BlockLegacy14getCommandNameEv");
    FakeNative((void **) &fake_BlockLegacy_getRawName, "_ZNK11BlockLegacy12getRawNameIdEv");
    //方块类
    FakeNative((void **) &fake_Block_getRuntimeId, "_ZNK5Block12getRuntimeIdEv");
    //方块数据类
    FakeNative((void **) &fake_BlockSource_getBlock, "_ZNK11BlockSource8getBlockEiii");
    //方块注册类
    FakeNative((void **) &fake_BlockTypeRegistry_registerBlock, "_ZN17BlockTypeRegistry13registerBlockI11BlockLegacyJRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK8MaterialEEERT_DpOT0_");
    FakeNative((void **) &fake_BlockTypeRegistry_lookupByName, "_ZN17BlockTypeRegistry12lookupByNameERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEb");
    FakeNative((void **) &fake_BlockTypeRegistry_mBlockLookupMap, "_ZN17BlockTypeRegistry15mBlockLookupMapE");
    //方块显示类
    FakeNative((void **) &fake_BlockGraphics_setTextureItem, "_ZN13BlockGraphics14setTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
    FakeNative((void **) &fake_BlockGraphics_getBlock, "_ZNK13BlockGraphics8getBlockEv");
    FakeNative((void **) &fake_BlockGraphics_setDefaultCarriedTextures, "_ZN13BlockGraphics25setDefaultCarriedTexturesEv");
    FakeNative((void **) &fake_BlockGraphics_setCarriedTextures, "_ZN13BlockGraphics21setCarriedTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
    //物品类
    FakeNative((void **) &fake_Item_getId, "_ZNK4Item5getIdEv");
    FakeNative((void **) &fake_ItemRegistry_mMaxItemID, "_ZN12ItemRegistry10mMaxItemIDE");
    FakeNative((void **) &fake_ItemRegistry_registerItemShared, "_ZN12ItemRegistry18registerItemSharedI4ItemJRsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEDpOT0_");
    FakeNative((void **) &fake_ItemStackBase_getId, "_ZNK13ItemStackBase5getIdEv");
    FakeNative((void **) &fake_Item_getCommandName, "_ZNK4Item14getCommandNameEv");
    FakeNative((void **) &fake_Item_setCategory, "_ZN4Item11setCategoryE20CreativeItemCategory");
    FakeNative((void **) &fake_Item_isFood, "_ZNK4Item6isFoodEv");
    FakeNative((void **) &fake_Item_isSeed, "_ZNK4Item6isSeedEv");
    FakeNative((void **) &fake_Item_getFullItemName, "_ZNK4Item15getFullItemNameEv");
    FakeNative((void **) &fake_Item_addTag, "_ZN4Item6addTagERK12HashedString");
    FakeNative((void **) &fake_Item_initClient, "_ZN4Item10initClientERN4Json5ValueES2_");
    FakeNative((void **) &fake_Item_setMaxDamage, "_ZN4Item12setMaxDamageEi");
    FakeNative((void **) &fake_Item_setMaxStackSize, "_ZN4Item15setMaxStackSizeEh");
    FakeNative((void **) &fake_Item_toBlockId, "_ZN4Item9toBlockIdEs");
    FakeNative((void **) &fake_Item_getLegacyBlock, "_ZNK4Item14getLegacyBlockEv");
    //没用
    FakeNative((void **) &fake_HashedString_c_str, "_ZNK12HashedString5c_strEv");
    FakeNative((void **) &fake_HashedString_HashedString, "_ZN12HashedStringC2EPKc");
    FakeNative((void **) &fake_HashedString_getString, "_ZNK12HashedString9getStringEv");
    //json库(没大用
    FakeNative((void **) &fake_Json_Value_size, "_ZNK4Json5Value4sizeEv");
    FakeNative((void **) &fake_Json_Value_asCString, "_ZNK4Json5Value9asCStringEv");
    FakeNative((void **) &fake_Json_Value_getMemberNames, "_ZNK4Json5Value14getMemberNamesEv");
    FakeNative((void **) &fake_Json_Value_resolveReference, "_ZN4Json5Value16resolveReferenceEPKcb");
    FakeNative((void **) &fake_Json_Value_toStyledString, "_ZNK4Json5Value14toStyledStringEv");
    FakeNative((void **) &fake_Json_Reader_parse, "_ZN4Json6Reader5parseEPKcS2_RNS_5ValueEb");
    FakeNative((void **) &fake_Json_Reader_Reader, "_ZN4Json6ReaderC2Ev");
    FakeNative((void **) &fake_Json_Value_Value, "_ZN4Json5ValueC2ENS_9ValueTypeE");
    FakeNative((void **) &fake_Json_Value_append, "_ZN4Json5Value6appendERKS0_");
    //物品注册
    FakeNative((void **) &fake_ItemRegistry_registerItemSharedForSword, "_ZN12ItemRegistry18registerItemSharedI10WeaponItemJRsRKN4Item4TierEEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNSA_11char_traitsIcEENSA_9allocatorIcEEEEDpOT0_");
    //FakeNative((void **) &fake_ItemRegistry_registerBlockItemShared, "_ZN12ItemRegistry18registerItemSharedI9BlockItemJsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEDpOT0_");//没用，系统自动调用注册
    FakeNative((void **) &fake_ItemRegistry_getItemById, "_ZN12ItemRegistry7getItemEs");
    //FakeNative((void **) &fake_ItemRegistry_registerLegacyID, "_ZN12ItemRegistry16registerLegacyIDERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEE");
    FakeNative((void **) &fake_ItemRegistry_getNameFromLegacyID, "_ZN12ItemRegistry19getNameFromLegacyIDEs");
    //工具等级
    FakeNative((void **) &fake_Tier_getUses, "_ZNK4Item4Tier7getUsesEv");
    FakeNative((void **) &fake_Tier_getAttackDamageBonus, "_ZNK4Item4Tier20getAttackDamageBonusEv");
    //材料
    FakeNative((void **) &fake_Material_getMaterial, "_ZN8Material11getMaterialE12MaterialType");
    //杂项
    FakeNative((void **) &fake_FoodSaturationFromString, "_Z24FoodSaturationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE");
    FakeNative((void **) &fake_UseAnimationFromString, "_Z22UseAnimationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE");
    //FakeNative((void **) &fake_setBlockDisplayName, "_ZN6Social11UserProfile14setDisplayNameERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE_0");
    //FakeNative((void **) &fake_FoodItemComponentLegacy, "_ZN23FoodItemComponentLegacyC2ER4Item");//没用
    FakeNative((void **) &fake_ItemInstance_Item, "_ZN12ItemInstanceC1ERK4Item");
    // hook区
    //方块类
    InLineHook((void *) NC_Block_onPlace, (void **) &base_Block_onPlace, "_ZNK5Block7onPlaceER11BlockSourceRK8BlockPosRKS_");
    //Legacy方块类
    InLineHook((void *) NC_BlockLegacy_setExplodeable, (void **) &base_BlockLegacy_setExplodeable, "_ZN11BlockLegacy14setExplodeableEf");
    //物品类
    InLineHook((void *) NC_Item_Item, (void **) &base_Item_Item, "_ZN4ItemC1ERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEs");
    InLineHook((void *) NC_Item_useOn, (void **) &base_Item_useOn, "_ZNK4Item5useOnER9ItemStackR5Actoriiihfff");
    InLineHook((void *) NC_Item_addCreativeItem, (void **) &base_Item_addCreativeItem, "_ZN4Item15addCreativeItemEPS_s");
    //InLineHook((void *) NC_Item_addTag, (void **) &base_Item_addTag, "_ZN4Item6addTagERK12HashedString");//大概没大用(不知道怎么用
    InLineHook((void *) NC_Item_initServer, (void **) &base_Item_initServer, "_ZN4Item10initServerERN4Json5ValueE");
    InLineHook((void *) NC_Item_setIcon, (void **) &base_Item_setIcon, "_ZN4Item7setIconERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    //InLineHook((void *) NC_Item_initClient, (void **) &base_Item_initClient, "_ZN4Item10initClientERN4Json5ValueES2_");//似乎无用
    InLineHook((void *) NC_BlockItem__useOn, (void **) &base_BlockItem__useOn, "_ZNK9BlockItem6_useOnER9ItemStackR5Actor8BlockPoshfff");
    //原版物品管理类
    InLineHook((void *) NC_VanillaItems_registerItems, (void **) &base_VanillaItems_registerItems, "_ZN12VanillaItems13registerItemsERK11Experimentsb");
    InLineHook((void *) NC_VanillaItems_initClientData, (void **) &base_VanillaItems_initClientData, "_ZN12VanillaItems14initClientDataER11Experiments");
    InLineHook((void *) NC_VanillaItems_serverInitCreativeItemsCallback, (void **) &base_VanillaItems_serverInitCreativeItemsCallback, "_ZN12VanillaItems31serverInitCreativeItemsCallbackEP17ActorInfoRegistryP20BlockDefinitionGroupP20CreativeItemRegistrybRK15BaseGameVersionRK11Experiments");
    InLineHook((void *) NC_ItemRegistry_registerItemShared, (void **) &base_ItemRegistry_registerItemShared, "_ZN12ItemRegistry18registerItemSharedI4ItemJRsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEDpOT0_");
    InLineHook((void *) NC_ItemRegistry_registerItem, (void **) &base_ItemRegistry_registerItem, "_ZN12ItemRegistry12registerItemE9SharedPtrI4ItemE");
    //原版方块管理类
    InLineHook((void *) NC_VanillaBlockTypes_registerBlocks, (void **) &base_VanillaBlockTypes_registerBlocks, "_ZN17VanillaBlockTypes14registerBlocksERK11Experiments");
    //方块注册类
    InLineHook((void *) NC_BlockTypeRegistry_registerBlock, (void **) &base_BlockTypeRegistry_registerBlock, "_ZN17BlockTypeRegistry13registerBlockI11BlockLegacyJRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK8MaterialEEERT_DpOT0_");
    //方块显示类
    //InLineHook((void *) NC_BlockGraphics_initBlocks, (void **) &base_BlockGraphics_initBlocks, "_ZN13BlockGraphics10initBlocksER19ResourcePackManagerRK11Experiments");//暂时不用了
    InLineHook((void *) NC_BlockGraphics_BlockGraphics, (void **) &base_BlockGraphics_BlockGraphics, "_ZN13BlockGraphicsC2ERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
    //InLineHook((void *) NC_BlockGraphics_setTextureItem, (void **) &base_BlockGraphics_setTextureItem, "_ZN13BlockGraphics14setTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES8_S8_S8_S8_S8_");//暂时不用了
    //InLineHook((void *) NC_BlockGraphics_registerBlockGraphics, (void **) &base_BlockGraphics_registerBlockGraphics, "_ZN13BlockGraphics21registerBlockGraphicsERNSt6__ndk16vectorIN4Json5ValueENS0_9allocatorIS3_EEEERKNS0_12basic_stringIcNS0_11char_traitsIcEENS4_IcEEEE10BlockShape");
    InLineHook((void *) NC_BlockGraphics_registerLooseBlockGraphics, (void **) &base_BlockGraphics_registerLooseBlockGraphics, "_ZN13BlockGraphics26registerLooseBlockGraphicsERNSt6__ndk16vectorIN4Json5ValueENS0_9allocatorIS3_EEEE");
    //材料
    InLineHook((void *) NC_Material__setupSurfaceMaterials, (void **) &base_Material__setupSurfaceMaterials, "_ZN8Material22_setupSurfaceMaterialsEv");
    //fake原版工具等级
    SwordItemFactory::tiersPool["Wood"] = new Item::Tier(0, 59, 2.0, 0, 15);//木
    SwordItemFactory::tiersPool["Stone"] = new Item::Tier(1, 131, 4.0, 1, 5);//石
    SwordItemFactory::tiersPool["Iron"] = new Item::Tier(2, 250, 6.0, 2, 14);//铁
    SwordItemFactory::tiersPool["Gold"] = new Item::Tier(3, 1561, 8.0, 3, 10);//钻石
    SwordItemFactory::tiersPool["Diamond"] = new Item::Tier(0, 32, 12.0, 0, 22);//金
    SwordItemFactory::tiersPool["Netherite"] = new Item::Tier(4, 2031, 9.0, 4, 15);//下届合金
    //历史遗留问题
    //ptr = (void *)dlsym(this->MCHandle, "_ZN4Item7setIconERK22TextureUVCoordinateSet");
    //MSHookFunction(ptr, (void *)&EX_Item_setIcon1, (void **)&base_Item_setIcon1);
    //InLineHook((void *)EX_Item_getIcon, (void **)&base_Item_getIcon, "_ZNK4Item7getIconERK13ItemStackBaseib");
    //ptr = (void *)dlsym(this->MCHandle, "_ZN13ItemStackBaseC2ERK4Itemii");
    //MSHookFunction(ptr, (void *)&EX_ItemStackBase, (void **)&base_ItemStackBase);
    //ptr = (void *)dlsym(this->MCHandle, "_ZN22TextureUVCoordinateSetC1Efffftt16ResourceLocationft");
    //MSHookFunction(ptr, (void *)&EX_TextureUVCoordinateSet_TextureUVCoordinateSet, (void **)&base_TextureUVCoordinateSet_TextureUVCoordinateSet);
    //ptr = (void *)dlsym(this->MCHandle, "_ZN4Item25getTextureUVCoordinateSetERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    //MSHookFunction(ptr, (void *)&EX_Item_getTextureUVCoordinateSet, (void **)&base_Item_getTextureUVCoordinateSet);
    //ptr = (void *)dlsym(this->MCHandle, "_Z15setIconIfLegacyRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEES7_i");
    //MSHookFunction(ptr, (void *)&test_, (void **)&test11);
}

#endif