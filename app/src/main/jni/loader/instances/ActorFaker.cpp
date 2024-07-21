
#include "headers/feifan/BlockSourceFaker.hpp"

class Actor
{
};
// 
// fake区域
#define def(type, method, args...) type (*fake_##method) (args)

def(BlockSource*, Actor_getRegion, Actor*);
def(bool, Actor_isSneaking, Actor*);
