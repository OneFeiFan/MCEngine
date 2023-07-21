#ifndef EX_FAKE_BLOCKSOURCE_HPP
#define EX_FAKE_BLOCKSOURCE_HPP
#include <dlfcn.h>
class BlockPos;
class Block;
class LevelChunk;
class BlockSource
{
public:
    //void removeBlock(int, int, int);
    Block *getBlock(const BlockPos&) const;
    LevelChunk* getChunk(int, int) const;

};//
// fake区域
Block * (*Fake_BlockSource_getBlock)(BlockSource *,int,int,int);
#endif