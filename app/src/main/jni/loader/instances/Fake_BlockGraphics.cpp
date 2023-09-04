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

std::map<std::string, BlockGraphics *> blockGraphicsPool;//存放BlockGraphics对象指针，并以方块名为索引
//fake区

BlockGraphics *(*fake_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &);

BlockGraphics *(*fake_BlockGraphics_setDefaultCarriedTextures)(BlockGraphics *);

BlockGraphics *(*fake_BlockGraphics_setCarriedTextures)(BlockGraphics *, std::string const &);

Block *(*fake_BlockGraphics_getBlock)(BlockGraphics *);
//hook区

void (*base_BlockGraphics_registerLooseBlockGraphics)(std::vector<Json::Value> &);

void NC_BlockGraphics_registerLooseBlockGraphics(std::vector<Json::Value> &data)
{
    auto *value = new Json::Value();
    auto *reader = new Json::Reader();
    const char *c = "{ \"format_version\": [1,1,0],\"block_Temp\":{}}";
    reader -> parse(c, c + strlen(c), *value);
    //free(&data[0]);//释放原内存
    memcpy(&data[0], value, sizeof(value));//强制拷贝新内存
    base_BlockGraphics_registerLooseBlockGraphics(data);
    BlockGraphics * ptr = blockGraphicsPool.find("block_Temp")->second;
    fake_BlockGraphics_setTextureItem(ptr, "bee_nest_top");
    fake_BlockGraphics_setCarriedTextures(ptr, "bee_nest_top");
    fake_BlockGraphics_setDefaultCarriedTextures(ptr);
    blockGraphicsPool.clear();
    blockGraphicsPool.~map();
}

//void (*base_BlockGraphics_initBlocks)(BlockGraphics *, ResourcePackManager &, Experiments const &);
//
//void NC_BlockGraphics_initBlocks(BlockGraphics *ptr, ResourcePackManager &a, Experiments const &b)
//{
//    base_BlockGraphics_initBlocks(ptr, a, b);
//}

BlockGraphics *(*base_BlockGraphics_BlockGraphics)(BlockGraphics *, std::string const &);

BlockGraphics *NC_BlockGraphics_BlockGraphics(BlockGraphics *ptr, std::string const &str)
{
    blockGraphicsPool[str] = ptr;
    return base_BlockGraphics_BlockGraphics(ptr, str);
}

//BlockGraphics *(*base_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &);
//
//BlockGraphics *NC_BlockGraphics_setTextureItem(BlockGraphics *ptr, std::string const &a, std::string const &b, std::string const &c, std::string const &d, std::string const &e, std::string const &f)
//{
//    return base_BlockGraphics_setTextureItem(ptr, a, b, c, d, e, f);;
//}