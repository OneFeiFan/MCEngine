#ifndef EX_FAKE_ACTOR_HPP
#define EX_FAKE_ACTOR_HPP
#include <dlfcn.h>

class Actor
{
};
// 
// fake区域
extern int (*fake_Actor_getRegion)(Actor *);
extern bool (*fake_Actor_isSneaking)(Actor *);
// fake_Actor_getRegion = ()dlsym(RTLD_DEFAULT, "_ZN4Item11setCategoryE20CreativeItemCategory");
#endif