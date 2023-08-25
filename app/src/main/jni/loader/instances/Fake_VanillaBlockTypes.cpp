//
// Created by 30225 on 2023/8/23.
//

#include "headers/Fake_VanillaBlockTypes.hpp"
#include "headers/Fake_BlockTypeRegistry.hpp"
#include "headers/Fake_ItemRegistry.h"
#include <iostream>

BlockLegacy *tempBlock;

void (*base_VanillaBlockTypes_registerBlocks)(VanillaBlockTypes *, Experiments const &);

void NC_VanillaBlockTypes_registerBlocks(VanillaBlockTypes *ptr, Experiments const &e)
{
    printf("开始注册方块");
    base_VanillaBlockTypes_registerBlocks(ptr, e);
    int id = 20000;
    tempBlock = fake_BlockTypeRegistry_registerBlock("block_Temp", &id, *materialsPool[3]);
    tempBlock = fake_BlockLegacy_setDestroyTime(tempBlock, 5.0);
    tempBlock = fake_BlockLegacy_setExplodeable(tempBlock, 5.0);
    tempBlock = fake_BlockLegacy_setCategory(tempBlock, 1);
    std::cout << fake_BlockLegacy_getRawName(tempBlock) << std::endl;
    printf("注册");
//  Dl_info info;
//  dladdr((uintptr_t *)(*(int (__fastcall **)(BlockLegacy *, const ItemState *, uintptr_t))(*(uintptr_t *)tempBlock + 576)),&info);
//  std::cout<<info.dli_sname<<std::endl;
    printf("开始注册方块完成");
}