//
// Created by 30225 on 2023/8/25.
//

#ifndef MCENGINE_NC_BLOCKS_HPP
#define MCENGINE_NC_BLOCKS_HPP
//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改

#include "../../headers/CreativeItemCategory.h"
#include "headers/Fake_BlockLegacy.hpp"
#include <vector>

class NC_Blocks
{
private:
    const char *name;
    const char *textureName;
    int textureData;
    int material;
    const CreativeItemCategory category;
    BlockLegacy *ptr;

//    float hardness = 1.5;//原版硬度是destroyTime，突出一个屎山不改
//    float blastResistance = 10;//原版抗爆是explodeable。。。。。。。
public:
    NC_Blocks(const char *, const char *, int, const CreativeItemCategory, int);

    static NC_Blocks *createObj(const char *, const char *, int, const CreativeItemCategory, int);

    const char *getName() const;

    const CreativeItemCategory getCategory() const;

    int getMaterial() const;

    const char *getTextureName() const;

    int getTextureData() const;

    BlockLegacy *getBlockPtr() const;

    void setBlockPtr(BlockLegacy *ptr);
};

extern std::vector<NC_Blocks *> blocksPoolArray;
//最终值=(5/3)*抗性

#endif //MCENGINE_NC_BLOCKS_HPP
