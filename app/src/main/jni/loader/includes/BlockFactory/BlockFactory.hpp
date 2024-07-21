//
// Created by 30225 on 2023/8/25.
//

#ifndef MCENGINE_BLOCKFACTORY_HPP
#define MCENGINE_BLOCKFACTORY_HPP
//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改

#include "../../headers/mojang/CreativeItemCategory.h"
#include "headers/feifan/BlockLegacyFaker.hpp"
#include "headers/feifan/MaterialFaker.hpp"
#include "../../headers/mojang/BlockLegacy.h"
#include <vector>

class BlockFactory
{
private:
    const char *name;
    const char *textureName;
    int textureData;
    const char * material;
    const CreativeItemCategory category;
    BlockLegacy *ptr;
//    float hardness = 1.5;//原版硬度是destroyTime，突出一个屎山不改
//    float blastResistance = 10;//原版抗爆是explodeable。。。。。。。
public:
    static std::vector<BlockFactory*> blocksPoolArray;
    BlockFactory(const char * name, const char * textureName, int textureData, const CreativeItemCategory category, const char * material): name(name),textureName(textureName),textureData(textureData),category(category),material(material){
        ptr = nullptr;
    };
    static BlockFactory *createObj(const char *name, const char *textureName,int textureData, const CreativeItemCategory type,const char * material) {
        auto* block = new BlockFactory(name, textureName, textureData, type,material);
        blocksPoolArray.emplace_back(block);
        return block;
    }
    const char *getName() const {
        return name;
    }
    CreativeItemCategory getCategory() const {
        return category;
    }
    const char * getMaterial() const {
        return material;
    }
    const char *getTextureName() const {
        return textureName;
    }
    int getTextureData() const {
        return textureData;
    }
    BlockLegacy *getBlockPtr() const {
        return ptr;
    }
    void setBlockPtr(BlockLegacy *blockLegacy) {
        ptr = blockLegacy;
    }
};
//最终值=(5/3)*抗性

#endif //MCENGINE_BLOCKFACTORY_HPP
