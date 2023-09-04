//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "NC_Items.hpp"
#include "tester/android.hpp"

std::vector<NC_Items *> normalItemsPoolArray;
std::map<short,Item::Tier *> tiersPool;
std::vector<Item*> NC_Items::items;
jobject NC_Items::NativeItemClass;

NC_Items::NC_Items(const char *name, const char *iconName, int iconData, const CreativeItemCategory type) : name(name), iconName(iconName), iconData(iconData), type(type)
{
    ptr = nullptr;
}

NC_Items* NC_Items::createObj(const char *name, const char *iconName,int iconData, const CreativeItemCategory type)
{
    NC_Items* item = new NC_Items(name, iconName, iconData, type);
    normalItemsPoolArray.emplace_back(item);
    //items.emplace_back()
    return item;
}

void NC_Items::setItemPtr(Item *ptr_)
{
    ptr = ptr_;
}

const char *NC_Items::getName() const
{
    return name;
}

const char *NC_Items::getIconName() const
{
    return iconName;
}

int NC_Items::getIconData() const
{
    return iconData;
}

Item *NC_Items::getPtr()
{
    return ptr;
}

CreativeItemCategory NC_Items::getType()
{
    return type;
}

void NC_Items::useOn(Item *item, ItemStack &, Actor &, int, int, int, unsigned char, float, float, float)
{
    JNIEnv* env = android::getJNIEnv();
    jclass NativeItemPtr = env->FindClass("com/taolesi/mcengine/NativeItem");
    jmethodID id = env->GetMethodID(NativeItemPtr, "onItemUse", "()V");
    //const char *_charName = str.c_str();
    //jstring _jName = env->NewStringUTF(_charName);
    env->CallVoidMethod(NativeItemClass, id);
}


