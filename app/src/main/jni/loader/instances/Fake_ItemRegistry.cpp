//
// Created by 30225 on 2023/7/26.
//
#include "../headers/Fake_ItemRegistry.h"

ItemRegistry *(*fake_ItemRegistry_mMaxItemID);

WeakPtr<Item> (*fake_ItemRegistry_registerItemShared)(std::string const &, short &);

WeakPtr<Item> (*fake_ItemRegistry_registerItemSharedForSword)(std::string const &, short &,Item::Tier const&);