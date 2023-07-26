//
// Created by 30225 on 2023/7/26.
//

#ifndef MCENGINE_FAKE_VANILLAITEMS_H
#define MCENGINE_FAKE_VANILLAITEMS_H

class Experiments;
class ActorInfoRegistry;

class BlockDefinitionGroup;

class BaseGameVersion;
class CreativeItemRegistry;

//hook区
extern void *(*base_VanillaItems_registerItems)(void *, Experiments const &, bool);

extern void *NC_VanillaItems_registerItems(void *ptr, Experiments const &e, bool b);

extern void *(*base_VanillaItems_initClientData)(void *, Experiments const &);

extern void *NC_VanillaItems_initClientData(void *ptr, Experiments const &e);

extern void *(*base_VanillaItems_serverInitCreativeItemsCallback)(void *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, bool, BaseGameVersion const &, Experiments const &);

extern void *NC_VanillaItems_serverInitCreativeItemsCallback(void *ptr, ActorInfoRegistry *a, BlockDefinitionGroup *b, CreativeItemRegistry *c, bool d, BaseGameVersion const &e, Experiments const &f);

#endif //MCENGINE_FAKE_VANILLAITEMS_H
