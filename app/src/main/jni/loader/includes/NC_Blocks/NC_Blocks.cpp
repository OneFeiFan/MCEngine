//
// Created by 30225 on 2023/8/25.
//

#include <iostream>
#include "NC_Blocks.hpp"
std::vector<NC_Blocks *> blocksPoolArray;
NC_Blocks::NC_Blocks(const char * name, const char * textureName,int textureData, const CreativeItemCategory category,const char * material):name(name),textureName(textureName),textureData(textureData),category(category),material(material){
    ptr = nullptr;
}
NC_Blocks* NC_Blocks::createObj(const char *name, const char *textureName,int textureData, const CreativeItemCategory type,const char * material)
{
    auto* block = new NC_Blocks(name, textureName, textureData, type,material);
    blocksPoolArray.emplace_back(block);
    return block;
}

CreativeItemCategory NC_Blocks::getCategory() const
{
    return category;
}

const char * NC_Blocks::getMaterial() const
{
    return material;
}

const char *NC_Blocks::getTextureName() const
{
    return textureName;
}

int NC_Blocks::getTextureData() const
{
    return textureData;
}

const char *NC_Blocks::getName() const
{
    return name;
}

BlockLegacy *NC_Blocks::getBlockPtr() const
{
    return ptr;
}

void NC_Blocks::setBlockPtr(BlockLegacy *blockLegacy)
{
    NC_Blocks::ptr = blockLegacy;
}
