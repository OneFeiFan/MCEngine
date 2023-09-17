//
// Created by 30225 on 2023/8/23.
//

#include "headers/Fake_VanillaBlockTypes.hpp"
#include "headers/Fake_BlockTypeRegistry.hpp"
#include "headers/Fake_ItemRegistry.hpp"
#include "headers/Other.hpp"
#include "NC_Blocks.hpp"
#include <iostream>


void (*base_VanillaBlockTypes_registerBlocks)(VanillaBlockTypes *, Experiments const &);

void NC_VanillaBlockTypes_registerBlocks(VanillaBlockTypes *ptr, Experiments const &e)
{
    forBlock = true;
    printf("开始注册方块");
    Item *itemPtr;
    BlockLegacy *blockPtr;
    base_VanillaBlockTypes_registerBlocks(ptr, e);
    int id = 20000;
    for(auto &NC_BlockPtr: blocksPoolArray){
        blockPtr = fake_BlockTypeRegistry_registerBlock(NC_BlockPtr->getName(), &id, *materialsPool[NC_BlockPtr->getMaterial()]);
        fake_BlockLegacy_setCategory(blockPtr, NC_BlockPtr->getCategory());
        blockPtr = fake_BlockLegacy_createWeakPtr(blockPtr).get();
        NC_BlockPtr->setBlockPtr(blockPtr);
        ++id;
    }
    printf("注册");

//  Dl_info info;
//  dladdr((uintptr_t *)(*(int (__fastcall **)(BlockLegacy *, const ItemState *, uintptr_t))(*(uintptr_t *)tempBlock + 576)),&info);
//  std::cout<<info.dli_sname<<std::endl;
    printf("开始注册方块完成");
}