//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/Fake_VanillaItems.h"
#include "../headers/Fake_Item.h"
#include "../headers/Fake_ItemRegistry.h"
#include "NC_Items.hpp"
#include "headers/Fake_HashedString.h"
#include "headers/fake_FoodItemComponentLegacy.h"
#include "NC_FoodItems.hpp"
#include "NC_SwordItems.hpp"

class Experiments;

//hook区
void *(*base_VanillaItems_registerItems)(void *, Experiments const &, bool);

void *NC_VanillaItems_registerItems(void *ptr, Experiments const &e, bool b)
{
    printf("注册物品开始\n");
    Item *itemPtr;

    for(auto &NC_ItemPtr: normalItemsPoolArray){
        itemPtr = fake_ItemRegistry_registerItemShared(NC_ItemPtr->getName(), (short &) (++fake_ItemRegistry_mMaxItemID)).get();
        NC_ItemPtr->setItemPtr(itemPtr);
        if(NC_ItemPtr->isInCreative()){
            fake_Item_setCategory(itemPtr, NC_ItemPtr->getType());
        }else{
            fake_Item_setCategory(itemPtr, (CreativeItemCategory)0);
        }
    }
    printf("普通物品注册完成，一切正常\n");
    for(auto &NC_ItemPtr: swordItemsPoolArray){
        itemPtr = fake_ItemRegistry_registerItemSharedForSword(NC_ItemPtr->getName(), (short &) (++fake_ItemRegistry_mMaxItemID),*tiersPool[NC_ItemPtr->getTier()]).get();

        *((uint32_t *)itemPtr + 75) = NC_ItemPtr->getDamage();//设置攻击力
        fake_Item_setMaxDamage(itemPtr, NC_ItemPtr->getDurability());//设置耐久
        NC_ItemPtr->setItemPtr(itemPtr);
        if(NC_ItemPtr->isInCreative()){
            fake_Item_setCategory(itemPtr, NC_ItemPtr->getType());
        }else{
            fake_Item_setCategory(itemPtr, (CreativeItemCategory)0);
        }
    }
    printf("武器注册完成，一切正常\n");
    for(auto &NC_ItemPtr: foodItemsPoolArray){
        auto *value = new Json::Value();
        auto *reader = new Json::Reader();
        itemPtr = fake_ItemRegistry_registerItemShared(NC_ItemPtr->getName(), (short &) (++fake_ItemRegistry_mMaxItemID)).get();
        NC_ItemPtr->setItemPtr(itemPtr);
        fake_Item_setCategory(itemPtr, NC_ItemPtr->getType());
        reader->parse(NC_ItemPtr->getTypeData(), *value);
        const char * saturationLevel = (*value)["components"]["minecraft:food"]["saturation_modifier"].asCString();
        base_Item_initServer(itemPtr, *value);
        auto *fooderPtr = (FoodItemComponentLegacy *) *((uint32_t *) itemPtr + 66);//获取Item中和食物有关对象的地址
        *((uint8_t *) itemPtr + 22) = fake_UseAnimationFromString("eat");//写入使用动画
        *((uint32_t *) fooderPtr + 3) = fake_FoodSaturationFromString(saturationLevel);//写入营养值
        if(NC_ItemPtr->isInCreative()){
            fake_Item_setCategory(itemPtr, NC_ItemPtr->getType());
        }else{
            fake_Item_setCategory(itemPtr, (CreativeItemCategory)0);
        }
    }
    printf("物品注册完成，一切正常\n");
    return base_VanillaItems_registerItems(ptr, e, b);
}

void *(*base_VanillaItems_initClientData)(void *, Experiments const &);

void *NC_VanillaItems_initClientData(void *ptr, Experiments const &e)
{
    printf("开始设置图标\n");
    try{
        for(NC_Items *temp: normalItemsPoolArray){
            base_Item_setIcon(temp->getPtr(), temp->getIconName(), (short) temp->getIconData());
        }
        printf("普通物品图标设置完成\n");
        for(NC_Items *temp: swordItemsPoolArray){
            base_Item_setIcon(temp->getPtr(), temp->getIconName(), (short) temp->getIconData());
        }
        for(NC_Items *temp: foodItemsPoolArray){
            base_Item_setIcon(temp->getPtr(), temp->getIconName(), (short) temp->getIconData());
        }
    }catch(const std::exception &e){
        std::cerr << e.what() << '\n';
    }
    printf("物品图标设置完成\n");
    return base_VanillaItems_initClientData(ptr, e);
}

void *(*base_VanillaItems_serverInitCreativeItemsCallback)(void *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, bool, BaseGameVersion const &, Experiments const &);

void *NC_VanillaItems_serverInitCreativeItemsCallback(void *ptr, ActorInfoRegistry *a, BlockDefinitionGroup *b, CreativeItemRegistry *c, bool d, BaseGameVersion const &e, Experiments const &f)
{
    printf("当你看到这条输出，说明前面的注册，与设置图标一切正常\n");
    return base_VanillaItems_serverInitCreativeItemsCallback(ptr, a, b, c, d, e, f);
}