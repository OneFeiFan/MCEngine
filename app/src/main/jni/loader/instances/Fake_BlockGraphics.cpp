//
// Created by 30225 on 2023/8/29.
//

#include "headers/Fake_BlockGraphics.hpp"
#include "headers/Fake_BlockTypeRegistry.hpp"
#include "headers/Fake_Item.hpp"
#include "headers/Fake_VanillaBlockTypes.hpp"
#include "headers/Fake_ItemRegistry.hpp"
#include "headers/Fake_VanillaItems.hpp"
#include "headers/Fake_Block.hpp"
#include <iostream>
#include <string.h>

std::map<std::string, BlockGraphics *> blockGraphicsPool;

//fake区
BlockGraphics *(*fake_BlockGraphics_registerBlockGraphics)(std::vector<Json::Value> &, std::string const &, BlockShape);

BlockGraphics *(*fake_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &);

BlockGraphics *(*fake_BlockGraphics_BlockGraphics)(BlockGraphics *, std::string const &);

BlockGraphics *(*fake_BlockGraphics_lookupByName)(std::string const &, bool);

Block *(*fake_BlockGraphics_getBlock)(BlockGraphics *);

BlockGraphics *(*fake_BlockGraphics_setDefaultCarriedTextures)(BlockGraphics *);

std::unordered_map<unsigned int, BlockGraphics *> (*fake_BlockGraphics_mBlocks);

std::unordered_map<std::string, BlockGraphics *> (*fake_BlockGraphics_mBlockLookupMap);

std::vector<std::unique_ptr<BlockGraphics>> (*fake_BlockGraphics_mOwnedBlocks);

BlockGraphics *(*fake_BlockGraphics_setCarriedTextures)(BlockGraphics *, std::string const &);

//hook区
int aaaa = 0;

BlockGraphics *(*base_BlockGraphics_registerBlockGraphics)(std::vector<Json::Value> &, std::string const &, BlockShape);

BlockGraphics *NC_BlockGraphics_registerBlockGraphics(std::vector<Json::Value> &a, std::string const &b, BlockShape c)
{
    return base_BlockGraphics_registerBlockGraphics(a, b, c);
}

void (*base_BlockGraphics_registerLooseBlockGraphics)(std::vector<Json::Value> &);

void NC_BlockGraphics_registerLooseBlockGraphics(std::vector<Json::Value> &data)
{
    auto *value = new Json::Value();
    auto *reader = new Json::Reader();
    const char *c = "{ \"format_version\": [1,1,0],\"block_Temp\":{}}";
    reader->parse(c, c + strlen(c), *value);
    memcpy(&data[0], value, sizeof(value));

    base_BlockGraphics_registerLooseBlockGraphics(data);
}

void (*base_BlockGraphics_initBlocks)(BlockGraphics *, ResourcePackManager &, Experiments const &);

void NC_BlockGraphics_initBlocks(BlockGraphics *ptr, ResourcePackManager &a, Experiments const &b)
{
    base_BlockGraphics_initBlocks(ptr, a, b);
    fake_BlockGraphics_setTextureItem(blockGraphicsPool.find("block_Temp")->second, "bee_nest_top");
    fake_BlockGraphics_setCarriedTextures(blockGraphicsPool.find("block_Temp")->second, "bee_nest_top");
    fake_BlockGraphics_setDefaultCarriedTextures(blockGraphicsPool.find("block_Temp")->second);
}

BlockGraphics *(*base_BlockGraphics_BlockGraphics)(BlockGraphics *, std::string const &);

BlockGraphics *NC_BlockGraphics_BlockGraphics(BlockGraphics *ptr, std::string const &str)
{

    BlockGraphics *temp = base_BlockGraphics_BlockGraphics(ptr, str);
    blockGraphicsPool[str] = ptr;
    return temp;
}

BlockGraphics *(*base_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &);

BlockGraphics *NC_BlockGraphics_setTextureItem(BlockGraphics *ptr, std::string const &a, std::string const &b, std::string const &c, std::string const &d, std::string const &e, std::string const &f)
{
    return base_BlockGraphics_setTextureItem(ptr, a, b, c, d, e, f);;
}

BlockGraphics *(*base_BlockGraphics_lookupByName)(std::string const &, bool);

BlockGraphics *NC_BlockGraphics_lookupByName(std::string const &str, bool b)
{
    return base_BlockGraphics_lookupByName(str, b);
}