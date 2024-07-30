#ifndef EX_Fake_ITEMREGISTRY_HPP
#define EX_Fake_ITEMREGISTRY_HPP

#include <dlfcn.h>
#include "ItemFaker.hpp"

// fake区域
//#define Extern(type, method, args...) extern type (*fake_##method) (args)
extern short (*fake_ItemRegistry_mMaxItemID);
extern WeakPtr<Item> (*fake_ItemRegistry_registerItemShared) (std::string const&, short&);
extern WeakPtr<Item> (*fake_ItemRegistry_registerItemSharedForSword) (std::string const &, short &, Item::Tier const&);
extern WeakPtr<Item> (*fake_ItemRegistry_getItemById) (short);
extern WeakPtr<Item> (*fake_ItemRegistry_registerItem) (SharedPtr<Item>);
extern const char* (*fake_ItemRegistry_getNameFromLegacyID) (short);
//extern void (*fake_ItemRegistry_registerLegacyID) (std::string const&, short);


//hook区
//#define Extern(type, method, args...) extern type (*base_##method) (args)
extern WeakPtr<Item> (*base_ItemRegistry_registerItemShared) (std::string const &, short &);
extern int (*base_ItemRegistry_registerItem) (SharedPtr<Item>);

//#define Extern(type, method, args...) extern type method (args)
extern WeakPtr<Item> NC_ItemRegistry_registerItemShared (std::string const &, short &);
extern int NC_ItemRegistry_registerItem (SharedPtr<Item>);

#endif