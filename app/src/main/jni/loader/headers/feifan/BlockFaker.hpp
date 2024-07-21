//
// Created by 30225 on 2023/9/1.
//

#ifndef MCENGINE_BLOCKFAKER_HPP
#define MCENGINE_BLOCKFAKER_HPP


#include "headers/mojang/BlockSource.h"

extern void (*base_Block_onPlace)(void *, BlockSource &, BlockPos const &, Block const &);
extern void NC_Block_onPlace(void *ptr, BlockSource &blockSource, BlockPos const &pos, Block const &block);

//fake
extern unsigned int (*fake_Block_getRuntimeId)(Block *);
//_ZNK5Block12getRuntimeIdEv
#endif //MCENGINE_BLOCKFAKER_HPP
