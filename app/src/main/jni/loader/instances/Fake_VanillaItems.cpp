//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/Fake_VanillaItems.h"
#include "../headers/Fake_Item.h"
#include "../headers/Fake_ItemRegistry.h"
#include "NC_items.h"
#include "headers/Fake_HashedString.h"
#include "headers/fake_FoodItemComponentLegacy.h"

class Experiments;

//hook区
void *(*base_VanillaItems_registerItems)(void *, Experiments const &, bool);

void *NC_VanillaItems_registerItems(void *ptr, Experiments const &e, bool b)
{
    printf("base_VanillaItems_registerItems\n");
    //log::Toast("注册物品");
    Item *itemPtr;
    //HashedString *test = new HashedString();
    //fake_HashedString_HashedString(test,"minecraft:is_food");
    for(auto &NC_ItemPtr: normalItemsPoolArray){
        itemPtr = fake_ItemRegistry_registerItemShared(NC_ItemPtr->getName(), (short &) (++fake_ItemRegistry_mMaxItemID)).get();
        NC_ItemPtr->setItemPtr(itemPtr);
        normalItemsPoolMap.insert(std::pair<short &, NC_Items *>((short &) fake_ItemRegistry_mMaxItemID, NC_ItemPtr));
        fake_Item_setCategory(itemPtr, NC_ItemPtr->getType());
        //fake_Item_addTag(temp,test);
    }
    for(auto &NC_ItemPtr: foodItemsPoolArray){
        Json::Value *value = new Json::Value();
        Json::Reader *reader = new Json::Reader();
        itemPtr = fake_ItemRegistry_registerItemShared(NC_ItemPtr->getName(), (short &) (++fake_ItemRegistry_mMaxItemID)).get();
        NC_ItemPtr->setItemPtr(itemPtr);
        foodItemsPoolMap.insert(std::pair<short &, NC_Items *>((short &) fake_ItemRegistry_mMaxItemID, NC_ItemPtr));
        fake_Item_setCategory(itemPtr, NC_ItemPtr->getType());
        std::cout<<NC_ItemPtr->getTypeData()<<std::endl;
        reader->parse(NC_ItemPtr->getTypeData(), *value);
        const char * saturationLevel = (*value)["components"]["minecraft:food"]["saturation_modifier"].asCString();
        base_Item_initServer(itemPtr, *value);
        FoodItemComponentLegacy *fooderPtr = (FoodItemComponentLegacy *) *((uint32_t *) itemPtr + 66);//获取Item中和食物有关对象的地址
        *((uint8_t *) itemPtr + 22) = fake_UseAnimationFromString("eat");//写入使用动画
        *((uint32_t *) fooderPtr + 3) = fake_FoodSaturationFromString(saturationLevel);//写入营养值
    }
    return base_VanillaItems_registerItems(ptr, e, b);
}

void *(*base_VanillaItems_initClientData)(void *, Experiments const &);

void *NC_VanillaItems_initClientData(void *ptr, Experiments const &e)
{
    try{
        for(NC_Items *temp: normalItemsPoolArray){
            base_Item_setIcon(temp->getPtr(), temp->getIconName(), (short) temp->getIconData());
        }
        for(NC_Items *temp: foodItemsPoolArray){
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

    for(NC_Items *temp: normalItemsPoolArray){
        std::cout << 111 << std::endl;
    }
    return obj;
}