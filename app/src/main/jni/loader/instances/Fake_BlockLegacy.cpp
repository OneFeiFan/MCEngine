#include "../headers/Fake_BlockLegacy.hpp"

//
// Created by 30225 on 2023/8/23.
//
//fake区
unsigned int (*fake_BlockLegacy_getBlockItemId)(BlockLegacy *);

BlockLegacy * (*fake_BlockLegacy_createWeakPtr)(BlockLegacy *);

BlockLegacy *(*fake_BlockLegacy_setCategory)(BlockLegacy *, int);

BlockLegacy *(*fake_BlockLegacy_setDestroyTime)(BlockLegacy *, float );

BlockLegacy *(*fake_BlockLegacy_setExplodeable)(BlockLegacy *, float);

std::string (*fake_BlockLegacy_getCommandName)(BlockLegacy *);

std::string (*fake_BlockLegacy_getRawName)(BlockLegacy *);