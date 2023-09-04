//
// Created by 30225 on 2023/7/26.
//
#include <iostream>
#include "../headers/Fake_ItemRegistry.hpp"
#include "headers/Fake_VanillaBlockTypes.hpp"

ItemRegistry *(*fake_ItemRegistry_mMaxItemID);

WeakPtr<Item> (*fake_ItemRegistry_registerItemShared)(std::string const &, short &);

WeakPtr<Item> (*fake_ItemRegistry_registerItemSharedForSword)(std::string const &, short &, Item::Tier const &);

//WeakPtr<Item> (*fake_ItemRegistry_registerBlockItemShared)(std::string const &, short &);

WeakPtr<Item> (*fake_ItemRegistry_getItemById)(short);

//hook区