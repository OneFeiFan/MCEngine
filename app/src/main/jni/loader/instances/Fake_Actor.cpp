
#include "headers/Fake_BlockSource.hpp"

class Actor
{
};
// 
// fake区域
#define def(type, method, args...) type (*fake_##method) (args)

def(BlockSource*, Actor_getRegion, Actor*);
def(bool, Actor_isSneaking, Actor*);
