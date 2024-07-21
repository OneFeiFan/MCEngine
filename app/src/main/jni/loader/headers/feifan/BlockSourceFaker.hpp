#ifndef EX_FAKE_BLOCKSOURCE_HPP
#define EX_FAKE_BLOCKSOURCE_HPP
#include <dlfcn.h>
#include "headers/mojang/BlockSource.h"
#include "headers/mojang/Block.h"

class BlockPos;
class LevelChunk;

// fake区域
static Block * (*fake_BlockSource_getBlock)(BlockSource *,int,int,int);
#endif