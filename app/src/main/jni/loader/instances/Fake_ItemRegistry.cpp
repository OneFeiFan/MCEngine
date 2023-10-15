//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/Fake_ItemRegistry.hpp"
#include "headers/Fake_VanillaBlockTypes.hpp"

short (*fake_ItemRegistry_mMaxItemID);

WeakPtr<Item> (*fake_ItemRegistry_registerItemShared)(std::string const &, short &);
WeakPtr<Item> (*fake_ItemRegistry_registerItemSharedForSword)(std::string const &, short &, Item::Tier const &);
//WeakPtr<Item> (*fake_ItemRegistry_registerBlockItemShared)(std::string const &, short &);
WeakPtr<Item> (*fake_ItemRegistry_getItemById)(short);
const char*(*fake_ItemRegistry_getNameFromLegacyID)(short);
//void (*fake_ItemRegistry_registerLegacyID) (std::string const&, short);

WeakPtr<Item> (*fake_ItemRegistry_registerItem)(SharedPtr<Item>);
//hook区
WeakPtr<Item> (*base_ItemRegistry_registerItemShared)(std::string const &, short &);
WeakPtr<Item> NC_ItemRegistry_registerItemShared(std::string const &name, short &id)
{
    //std::cout << name << ": " << id << std::endl;
    return base_ItemRegistry_registerItemShared(name, id);
}

int (*base_ItemRegistry_registerItem)(SharedPtr<Item>);
int NC_ItemRegistry_registerItem(SharedPtr<Item> sharedPtr)
{
    //printf("%s", fake_Item_getFullItemName(sharedPtr.get()));

    //std::cout << fake_Item_getFullItemName(sharedPtr.get()) << ": " << fake_Item_getId(sharedPtr.get())<< std::endl;
    return base_ItemRegistry_registerItem(sharedPtr);
}