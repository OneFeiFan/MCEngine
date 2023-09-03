//
// Created by 30225 on 2023/8/23.
//

#include "headers/Fake_VanillaBlockTypes.hpp"
#include "headers/Fake_BlockTypeRegistry.hpp"
#include "headers/Fake_ItemRegistry.hpp"
#include "headers/Other.hpp"
#include <iostream>

BlockLegacy *tempBlock;

void (*base_VanillaBlockTypes_registerBlocks)(VanillaBlockTypes *, Experiments const &);

void NC_VanillaBlockTypes_registerBlocks(VanillaBlockTypes *ptr, Experiments const &e)
{
    printf("开始注册方块");
    Item *itemPtr;
    base_VanillaBlockTypes_registerBlocks(ptr, e);
    int id = 20000;
    //
    tempBlock = fake_BlockTypeRegistry_registerBlock("block_Temp", &id, *materialsPool[3]);
    tempBlock = fake_BlockLegacy_setDestroyTime(tempBlock, 5.0);
    tempBlock = fake_BlockLegacy_setExplodeable(tempBlock, 5.0);
    tempBlock = fake_BlockLegacy_setCategory(tempBlock, 1);
    std::cout << fake_BlockLegacy_getRawName(tempBlock) << std::endl;
    tempBlock = fake_BlockLegacy_createWeakPtr(tempBlock).get();
    //*((uint32_t *)tempBlock + 50) = 2;
    //fake_setBlockDisplayName()
    printf("注册");
//    try{
//        for(auto it = (*fake_BlockTypeRegistry_mBlockLookupMap).cbegin();it != (*fake_BlockTypeRegistry_mBlockLookupMap).cend();++it){
//            std::cout <<1 << std::endl;
//        }
//    }catch (...){
//
//    }


        //std::cout <<(**fake_BlockTypeRegistry_mBlockLookupMap).count("block_Temp")<< std::endl;
//
//  Dl_info info;
//  dladdr((uintptr_t *)(*(int (__fastcall **)(BlockLegacy *, const ItemState *, uintptr_t))(*(uintptr_t *)tempBlock + 576)),&info);
//  std::cout<<info.dli_sname<<std::endl;
    printf("开始注册方块完成");
}