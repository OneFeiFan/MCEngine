//
// Created by 30225 on 2023/9/1.
//

#include "../headers/feifan/BlockFaker.hpp"
//fake
unsigned int (*fake_Block_getRuntimeId)(Block *);
void (*base_Block_onPlace)(void *, BlockSource &, BlockPos const &, Block const &);

void NC_Block_onPlace(void *ptr, BlockSource &blockSource, BlockPos const &pos, Block const &block)
{
    return base_Block_onPlace(ptr, blockSource, pos, block);
}