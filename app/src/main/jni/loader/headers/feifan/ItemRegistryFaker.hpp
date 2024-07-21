#ifndef EX_Fake_ITEMREGISTRY_HPP
#define EX_Fake_ITEMREGISTRY_HPP

#include <dlfcn.h>
#include "ItemFaker.hpp"

// fake区域
#define Extern(type, method, args...) extern type (*fake_##method) (args)
extern short (*fake_ItemRegistry_mMaxItemID);
Extern(WeakPtr<Item>, ItemRegistry_registerItemShared, std::string const&, short&);
Extern(WeakPtr<Item>, ItemRegistry_registerItemSharedForSword, std::string const &, short &,Item::Tier const&);
Extern(WeakPtr<Item>, ItemRegistry_getItemById, short);
Extern(WeakPtr<Item>, ItemRegistry_registerItem, SharedPtr<Item>);
Extern(const char*, ItemRegistry_getNameFromLegacyID, short);
//Extern(void, ItemRegistry_registerLegacyID, std::string const&, short);

//hook区
#define Extern(type, method, args...) extern type (*base_##method) (args)
Extern(WeakPtr<Item>, ItemRegistry_registerItemShared, std::string const &, short &);
Extern(int, ItemRegistry_registerItem, SharedPtr<Item>);

#define Extern(type, method, args...) extern type method (args)
Extern(WeakPtr<Item>, NC_ItemRegistry_registerItemShared, std::string const &, short &);
Extern(int, NC_ItemRegistry_registerItem, SharedPtr<Item>);
#endif