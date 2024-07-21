#include "../headers/feifan/BlockLegacyFaker.hpp"
#include "headers/feifan/BlockSourceFaker.hpp"
#include "headers/feifan/ActorFaker.hpp"
#include "headers/mojang/CreativeItemCategory.h"
#include "headers/mojang/sharedptr.h"
#include <iostream>

//
// Created by 30225 on 2023/8/23.
//
//fake区
short (*fake_BlockLegacy_getBlockItemId)(BlockLegacy *);

WeakPtr<BlockLegacy> (*fake_BlockLegacy_createWeakPtr)(BlockLegacy *);

BlockLegacy *(*fake_BlockLegacy_setCategory)(BlockLegacy *, CreativeItemCategory);

BlockLegacy *(*fake_BlockLegacy_setDestroyTime)(BlockLegacy *, float);

BlockLegacy *(*fake_BlockLegacy_setExplodeable)(BlockLegacy *, float);

std::string (*fake_BlockLegacy_getCommandName)(BlockLegacy *);

char *(*fake_BlockLegacy_getRawName)(BlockLegacy *);

//hook区
BlockLegacy *(*base_BlockLegacy_setExplodeable)(BlockLegacy *, float);

BlockLegacy *NC_BlockLegacy_setExplodeable(BlockLegacy *ptr, float f)
{

//  Dl_info info;
//  dladdr((uintptr_t *)(*(uintptr_t (__fastcall **)(uintptr_t, BlockSource *, const BlockPos *, Actor *))(*(uintptr_t *)ptr + 1232LL)),&info);
//  std::cout<<info.dli_sname<<std::endl;
    return base_BlockLegacy_setExplodeable(ptr, f);
}