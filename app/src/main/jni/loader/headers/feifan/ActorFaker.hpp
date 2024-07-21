#ifndef EX_FAKE_ACTOR_HPP
#define EX_FAKE_ACTOR_HPP
#include "../mojang/Actor.h"
#include "ItemStackFaker.hpp"
#include "ItemStackBaseFaker.hpp"

// 
// fake区域
#define Extern(type, method, args...) extern type (*fake_##method)(args)
Extern(int, Actor_getRegion, Actor*);//fake_Actor_getRegion
Extern(bool, Actor_isSneaking, Actor*);//fake_Actor_isSneaking
// fake_Actor_getRegion = ()dlsym(RTLD_DEFAULT, "_ZN4Item11setCategoryE20CreativeItemCategory");
#endif