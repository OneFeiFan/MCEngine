//
// Created by 30225 on 2023/7/26.
//

#ifndef MCENGINE_FAKE_VANILLAITEMS_HPP
#define MCENGINE_FAKE_VANILLAITEMS_HPP

#include "Fake_Item.hpp"
class VanillaItems;
class Experiments;
class ActorInfoRegistry;

class BlockDefinitionGroup;

class BaseGameVersion;
class CreativeItemRegistry;

//hook区
extern void *(*base_VanillaItems_registerItems)(VanillaItems *, Experiments const &, bool);

extern void *NC_VanillaItems_registerItems(VanillaItems *ptr, Experiments const &e, bool b);

extern void *(*base_VanillaItems_initClientData)(VanillaItems *, Experiments const &);

extern void *NC_VanillaItems_initClientData(VanillaItems *, Experiments const &);

extern void (*base_VanillaItems_serverInitCreativeItemsCallback)(VanillaItems *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, Item *, BaseGameVersion const &, Experiments const &);

extern void NC_VanillaItems_serverInitCreativeItemsCallback(VanillaItems *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, Item * , BaseGameVersion const &, Experiments const &);

#endif //MCENGINE_FAKE_VANILLAITEMS_HPP
