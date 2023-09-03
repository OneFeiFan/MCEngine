#include "../headers/Fake_BlockLegacy.hpp"
#include "headers/Fake_BlockSource.hpp"
#include "headers/Fake_Actor.hpp"
#include <iostream>
//
// Created by 30225 on 2023/8/23.
//
//fake区
int (*fake_BlockLegacy_getBlockItemId)(BlockLegacy *);

WeakPtr<BlockLegacy> (*fake_BlockLegacy_createWeakPtr)(BlockLegacy *);

BlockLegacy *(*fake_BlockLegacy_setCategory)(BlockLegacy *, int);

BlockLegacy *(*fake_BlockLegacy_setDestroyTime)(BlockLegacy *, float );

BlockLegacy *(*fake_BlockLegacy_setExplodeable)(BlockLegacy *, float);

std::string (*fake_BlockLegacy_getCommandName)(BlockLegacy *);

char *(*fake_BlockLegacy_getRawName)(BlockLegacy *);

//hook区
BlockLegacy *(*base_BlockLegacy_setExplodeable)(BlockLegacy *, float);
BlockLegacy *NC_BlockLegacy_setExplodeable(BlockLegacy * ptr, float f){

//      Dl_info info;
//  dladdr((uintptr_t *)(*(uintptr_t (__fastcall **)(uintptr_t, BlockSource *, const BlockPos *, Actor *))(*(uintptr_t *)ptr + 1232LL)),&info);
//  std::cout<<info.dli_sname<<std::endl;
try {
//    std::string temp = fake_BlockLegacy_getRawName(ptr);
//    std::cout<<temp<<" "<<f<<std::endl;
}catch (...){
    std::cout<<"?????"<<std::endl;
}


    return base_BlockLegacy_setExplodeable(ptr,f);
}