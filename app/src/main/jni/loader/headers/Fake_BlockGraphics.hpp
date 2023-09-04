//
// Created by 30225 on 2023/8/29.
//

#ifndef MCENGINE_FAKE_BLOCKGRAPHICS_HPP
#define MCENGINE_FAKE_BLOCKGRAPHICS_HPP
#define BlockShape int

#include <vector>
#include "json/value.h"
#include "Fake_Block.hpp"
#include <unordered_map>

class ResourcePackManager;

class Experiments;

class BlockGraphics
{

};

//fake区

//设置默认方块贴图
extern BlockGraphics *(*fake_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &);

//设置默认方块手持时的贴图(实测是让fake_BlockGraphics_setTextureItem设置的贴图显示到放置的方块上
extern BlockGraphics *(*fake_BlockGraphics_setDefaultCarriedTextures)(BlockGraphics *);

//设置方块手持时的贴图(这才是真家伙
extern BlockGraphics *(*fake_BlockGraphics_setCarriedTextures)(BlockGraphics *, std::string const &);

//从BlockGraphics对象获取Block对象
extern Block *(*fake_BlockGraphics_getBlock)(BlockGraphics *);
//_ZN13BlockGraphics21setCarriedTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE
//hook区

extern void (*base_BlockGraphics_initBlocks)(BlockGraphics *, ResourcePackManager &, Experiments const &);

extern void NC_BlockGraphics_initBlocks(BlockGraphics *, ResourcePackManager &, Experiments const &);
//原构造函数
extern BlockGraphics *(*base_BlockGraphics_BlockGraphics)(BlockGraphics *, std::string const &);
//hook构造函数
extern BlockGraphics *NC_BlockGraphics_BlockGraphics(BlockGraphics *, std::string const &);

extern BlockGraphics *(*base_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &);

extern BlockGraphics *NC_BlockGraphics_setTextureItem(BlockGraphics *, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &);
//原设置单独方块显示函数
extern void (*base_BlockGraphics_registerLooseBlockGraphics)(std::vector<Json::Value> &);
//hook置单独方块显示函数
extern void NC_BlockGraphics_registerLooseBlockGraphics(std::vector<Json::Value> &);
//_ZN13BlockGraphics26registerLooseBlockGraphicsERNSt6__ndk16vectorIN4Json5ValueENS0_9allocatorIS3_EEEE
#endif //MCENGINE_FAKE_BLOCKGRAPHICS_HPP
