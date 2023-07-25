#ifndef EX_FAKE_ACTOR_HPP
#define EX_FAKE_ACTOR_HPP
#include <dlfcn.h>

class Actor
{
public:
    virtual int getDimensionId() const;

public:
    int getDimension() const;
};
// 
// fake区域
static int (*fake_Actor_getRegion)(Actor *);
static bool (*fake_Actor_isSneaking)(Actor *);
// fake_Actor_getRegion = ()dlsym(RTLD_DEFAULT, "_ZN4Item11setCategoryE20CreativeItemCategory");
#endif