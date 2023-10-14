//#include "includes/NC_HookFR/NCHookFR.h"
#include "JniToNative.hpp"
#include <iostream>
#include <cstring>
#include "includes/NC_Items/NC_Items.hpp"
#include "headers/Fake_Actor.hpp"
#include "headers/Fake_BlockSource.hpp"
#include "headers/Fake_BlockLegacy.hpp"
#include "headers/Fake_ItemStackBase.hpp"
#include "headers/Fake_ItemRegistry.hpp"
#include "headers/Fake_Item.hpp"
#include "headers/CreativeItemCategory.h"
#include "headers/Fake_VanillaItems.hpp"
#include "headers/Fake_HashedString.h"
#include "headers/Fake_Json_Value.hpp"
#include "headers/fake_FoodItemComponentLegacy.h"
#include "headers/Fake_VanillaBlockTypes.hpp"
#include "headers/Fake_Material.hpp"
#include "headers/Fake_BlockTypeRegistry.hpp"
#include "headers/Fake_BlockGraphics.hpp"
#include "headers/Other.hpp"
#include "headers/Fake_Block.hpp"
#include "headers/Fake_ItemInstance.hpp"

class CreativeItemRegistry;

void (*base_Block_onPlace)(void *, BlockSource &, BlockPos const &, Block const &);

void NC_Block_onPlace(void *ptr, BlockSource &blockSource, BlockPos const &pos, Block const &block)
{
    return base_Block_onPlace(ptr, blockSource, pos, block);
}

void NCHookFR::init()
{
    // fake区
    //实体/玩家？信息类
    NC_FakeNative((void **) &fake_Actor_getRegion, "_ZNK5Actor9getRegionEv");
    NC_FakeNative((void **) &fake_Actor_isSneaking, "_ZNK5Actor10isSneakingEv");
    //Legacy方块类
    NC_FakeNative((void **) &fake_BlockLegacy_getBlockItemId, "_ZNK11BlockLegacy14getBlockItemIdEv");
    NC_FakeNative((void **) &fake_BlockLegacy_createWeakPtr, "_ZN11BlockLegacy13createWeakPtrEv");
    NC_FakeNative((void **) &fake_BlockLegacy_setCategory, "_ZN11BlockLegacy11setCategoryE20CreativeItemCategory");
    NC_FakeNative((void **) &fake_BlockLegacy_setDestroyTime, "_ZN11BlockLegacy14setDestroyTimeEf");
    NC_FakeNative((void **) &fake_BlockLegacy_setExplodeable, "_ZN11BlockLegacy14setExplodeableEf");
    NC_FakeNative((void **) &fake_BlockLegacy_getCommandName, "_ZNK11BlockLegacy14getCommandNameEv");
    NC_FakeNative((void **) &fake_BlockLegacy_getRawName, "_ZNK11BlockLegacy12getRawNameIdEv");
    //方块类
    NC_FakeNative((void **) &fake_Block_getRuntimeId, "_ZNK5Block12getRuntimeIdEv");
    //方块数据类
    NC_FakeNative((void **) &fake_BlockSource_getBlock, "_ZNK11BlockSource8getBlockEiii");
    //方块注册类
    NC_FakeNative((void **) &fake_BlockTypeRegistry_registerBlock, "_ZN17BlockTypeRegistry13registerBlockI11BlockLegacyJRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK8MaterialEEERT_DpOT0_");
    NC_FakeNative((void **) &fake_BlockTypeRegistry_lookupByName, "_ZN17BlockTypeRegistry12lookupByNameERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEb");
    NC_FakeNative((void **) &fake_BlockTypeRegistry_mBlockLookupMap, "_ZN17BlockTypeRegistry15mBlockLookupMapE");
    //方块显示类
    NC_FakeNative((void **) &fake_BlockGraphics_setTextureItem, "_ZN13BlockGraphics14setTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
    NC_FakeNative((void **) &fake_BlockGraphics_getBlock, "_ZNK13BlockGraphics8getBlockEv");
    NC_FakeNative((void **) &fake_BlockGraphics_setDefaultCarriedTextures, "_ZN13BlockGraphics25setDefaultCarriedTexturesEv");
    NC_FakeNative((void **) &fake_BlockGraphics_setCarriedTextures, "_ZN13BlockGraphics21setCarriedTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
    //物品类
    NC_FakeNative((void **) &fake_Item_getId, "_ZNK4Item5getIdEv");
    NC_FakeNative((void **) &fake_ItemRegistry_mMaxItemID, "_ZN12ItemRegistry10mMaxItemIDE");
    NC_FakeNative((void **) &fake_ItemRegistry_registerItemShared, "_ZN12ItemRegistry18registerItemSharedI4ItemJRsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEDpOT0_");
    NC_FakeNative((void **) &fake_ItemStackBase_getId, "_ZNK13ItemStackBase5getIdEv");
    NC_FakeNative((void **) &fake_Item_getCommandName, "_ZNK4Item14getCommandNameEv");
    NC_FakeNative((void **) &fake_Item_setCategory, "_ZN4Item11setCategoryE20CreativeItemCategory");
    NC_FakeNative((void **) &fake_Item_isFood, "_ZNK4Item6isFoodEv");
    NC_FakeNative((void **) &fake_Item_isSeed, "_ZNK4Item6isSeedEv");
    NC_FakeNative((void **) &fake_Item_addTag, "_ZN4Item6addTagERK12HashedString");
    NC_FakeNative((void **) &fake_Item_initClient, "_ZN4Item10initClientERN4Json5ValueES2_");
    NC_FakeNative((void **) &fake_Item_setMaxDamage, "_ZN4Item12setMaxDamageEi");
    NC_FakeNative((void **) &fake_Item_setMaxStackSize, "_ZN4Item15setMaxStackSizeEh");
    NC_FakeNative((void **) &fake_Item_toBlockId, "_ZN4Item9toBlockIdEs");
    NC_FakeNative((void **) &fake_Item_getLegacyBlock, "_ZNK4Item14getLegacyBlockEv");
    //没用
    NC_FakeNative((void **) &fake_HashedString_c_str, "_ZNK12HashedString5c_strEv");
    NC_FakeNative((void **) &fake_HashedString_HashedString, "_ZN12HashedStringC2EPKc");
    //json库(没大用
    NC_FakeNative((void **) &fake_Json_Value_size, "_ZNK4Json5Value4sizeEv");
    NC_FakeNative((void **) &fake_Json_Value_asCString, "_ZNK4Json5Value9asCStringEv");
    NC_FakeNative((void **) &fake_Json_Value_getMemberNames, "_ZNK4Json5Value14getMemberNamesEv");
    NC_FakeNative((void **) &fake_Json_Value_resolveReference, "_ZN4Json5Value16resolveReferenceEPKcb");
    NC_FakeNative((void **) &fake_Json_Value_toStyledString, "_ZNK4Json5Value14toStyledStringEv");
    NC_FakeNative((void **) &fake_Json_Reader_parse, "_ZN4Json6Reader5parseEPKcS2_RNS_5ValueEb");
    NC_FakeNative((void **) &fake_Json_Reader_Reader, "_ZN4Json6ReaderC2Ev");
    NC_FakeNative((void **) &fake_Json_Value_Value, "_ZN4Json5ValueC2ENS_9ValueTypeE");
    NC_FakeNative((void **) &fake_Json_Value_append, "_ZN4Json5Value6appendERKS0_");
    //物品注册
    NC_FakeNative((void **) &fake_ItemRegistry_registerItemSharedForSword, "_ZN12ItemRegistry18registerItemSharedI10WeaponItemJRsRKN4Item4TierEEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNSA_11char_traitsIcEENSA_9allocatorIcEEEEDpOT0_");
    //NC_FakeNative((void **) &fake_ItemRegistry_registerBlockItemShared, "_ZN12ItemRegistry18registerItemSharedI9BlockItemJsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEDpOT0_");//没用，系统自动调用注册
    NC_FakeNative((void **) &fake_ItemRegistry_getItemById, "_ZN12ItemRegistry7getItemEs");
    //工具等级
    NC_FakeNative((void **) &fake_Tier_getUses, "_ZNK4Item4Tier7getUsesEv");
    NC_FakeNative((void **) &fake_Tier_getAttackDamageBonus, "_ZNK4Item4Tier20getAttackDamageBonusEv");
    //材料
    NC_FakeNative((void **) &fake_Material_getMaterial, "_ZN8Material11getMaterialE12MaterialType");
    //杂项
    NC_FakeNative((void **) &fake_FoodSaturationFromString, "_Z24FoodSaturationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE");
    NC_FakeNative((void **) &fake_UseAnimationFromString, "_Z22UseAnimationFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE");
    //NC_FakeNative((void **) &fake_setBlockDisplayName, "_ZN6Social11UserProfile14setDisplayNameERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE_0");
    //NC_FakeNative((void **) &fake_FoodItemComponentLegacy, "_ZN23FoodItemComponentLegacyC2ER4Item");//没用
    NC_FakeNative((void **) &fake_ItemInstance_Item, "_ZN12ItemInstanceC1ERK4Item");
    // hook区
    //方块类
    NC_InLineHook((void *) NC_Block_onPlace, (void **) &base_Block_onPlace, "_ZNK5Block7onPlaceER11BlockSourceRK8BlockPosRKS_");
    //Legacy方块类
    NC_InLineHook((void *) NC_BlockLegacy_setExplodeable, (void **) &base_BlockLegacy_setExplodeable, "_ZN11BlockLegacy14setExplodeableEf");
    //物品类
    NC_InLineHook((void *) NC_Item_useOn, (void **) &base_Item_useOn, "_ZNK4Item5useOnER9ItemStackR5Actoriiihfff");
    NC_InLineHook((void *) NC_Item_addCreativeItem, (void **) &base_Item_addCreativeItem, "_ZN4Item15addCreativeItemEPS_s");
    //NC_InLineHook((void *) NC_Item_addTag, (void **) &base_Item_addTag, "_ZN4Item6addTagERK12HashedString");//大概没大用(不知道怎么用
    NC_InLineHook((void *) NC_Item_initServer, (void **) &base_Item_initServer, "_ZN4Item10initServerERN4Json5ValueE");
    NC_InLineHook((void *) NC_Item_setIcon, (void **) &base_Item_setIcon, "_ZN4Item7setIconERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    //NC_InLineHook((void *) NC_Item_initClient, (void **) &base_Item_initClient, "_ZN4Item10initClientERN4Json5ValueES2_");//似乎无用
    NC_InLineHook((void *) NC_BlockItem__useOn, (void **) &base_BlockItem__useOn, "_ZNK9BlockItem6_useOnER9ItemStackR5Actor8BlockPoshfff");
    //原版物品管理类
    NC_InLineHook((void *) NC_VanillaItems_registerItems, (void **) &base_VanillaItems_registerItems, "_ZN12VanillaItems13registerItemsERK11Experimentsb");
    NC_InLineHook((void *) NC_VanillaItems_initClientData, (void **) &base_VanillaItems_initClientData, "_ZN12VanillaItems14initClientDataER11Experiments");
    NC_InLineHook((void *) NC_VanillaItems_serverInitCreativeItemsCallback, (void **) &base_VanillaItems_serverInitCreativeItemsCallback, "_ZN12VanillaItems31serverInitCreativeItemsCallbackEP17ActorInfoRegistryP20BlockDefinitionGroupP20CreativeItemRegistrybRK15BaseGameVersionRK11Experiments");
    NC_InLineHook((void *) NC_ItemRegistry_registerItemShared, (void **) &base_ItemRegistry_registerItemShared, "_ZN12ItemRegistry18registerItemSharedI4ItemJRsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEDpOT0_");
    //原版方块管理类
    NC_InLineHook((void *) NC_VanillaBlockTypes_registerBlocks, (void **) &base_VanillaBlockTypes_registerBlocks, "_ZN17VanillaBlockTypes14registerBlocksERK11Experiments");
    //方块注册类
    NC_InLineHook((void *) NC_BlockTypeRegistry_registerBlock, (void **) &base_BlockTypeRegistry_registerBlock, "_ZN17BlockTypeRegistry13registerBlockI11BlockLegacyJRKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEiRK8MaterialEEERT_DpOT0_");
    //方块显示类
    //NC_InLineHook((void *) NC_BlockGraphics_initBlocks, (void **) &base_BlockGraphics_initBlocks, "_ZN13BlockGraphics10initBlocksER19ResourcePackManagerRK11Experiments");//暂时不用了
    NC_InLineHook((void *) NC_BlockGraphics_BlockGraphics, (void **) &base_BlockGraphics_BlockGraphics, "_ZN13BlockGraphicsC2ERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
    //NC_InLineHook((void *) NC_BlockGraphics_setTextureItem, (void **) &base_BlockGraphics_setTextureItem, "_ZN13BlockGraphics14setTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES8_S8_S8_S8_S8_");//暂时不用了
    //NC_InLineHook((void *) NC_BlockGraphics_registerBlockGraphics, (void **) &base_BlockGraphics_registerBlockGraphics, "_ZN13BlockGraphics21registerBlockGraphicsERNSt6__ndk16vectorIN4Json5ValueENS0_9allocatorIS3_EEEERKNS0_12basic_stringIcNS0_11char_traitsIcEENS4_IcEEEE10BlockShape");
    NC_InLineHook((void *) NC_BlockGraphics_registerLooseBlockGraphics, (void **) &base_BlockGraphics_registerLooseBlockGraphics, "_ZN13BlockGraphics26registerLooseBlockGraphicsERNSt6__ndk16vectorIN4Json5ValueENS0_9allocatorIS3_EEEE");
    //材料
    NC_InLineHook((void *) NC_Material__setupSurfaceMaterials, (void **) &base_Material__setupSurfaceMaterials, "_ZN8Material22_setupSurfaceMaterialsEv");
    //fake原版工具等级
    tiersPool["Wood"] = new Item::Tier(0, 59, 2.0, 0, 15);//木
    tiersPool["Stone"] = new Item::Tier(1, 131, 4.0, 1, 5);//石
    tiersPool["Iron"] = new Item::Tier(2, 250, 6.0, 2, 14);//铁
    tiersPool["Gold"] = new Item::Tier(3, 1561, 8.0, 3, 10);//钻石
    tiersPool["Diamond"] = new Item::Tier(0, 32, 12.0, 0, 22);//金
    tiersPool["Netherite"] = new Item::Tier(4, 2031, 9.0, 4, 15);//下届合金
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