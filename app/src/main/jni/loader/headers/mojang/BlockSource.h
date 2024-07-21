//
// Created by 25843 on 2024/7/21.
//

#ifndef MCENGINE_BLOCKSOURCE_H
#define MCENGINE_BLOCKSOURCE_H

#include "Block.h"
class BlockPos;
class LevelChunk;
class BlockSource
{
public:
    //void removeBlock(int, int, int);
    Block *getBlock(const BlockPos&) const;
    LevelChunk* getChunk(int, int) const;

};//
#endif //MCENGINE_BLOCKSOURCE_H
