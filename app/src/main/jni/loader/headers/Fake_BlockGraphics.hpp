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
extern BlockGraphics *(*fake_BlockGraphics_registerBlockGraphics)(std::vector<Json::Value> &, std::string const &, BlockShape);

extern BlockGraphics *(*fake_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &);

extern BlockGraphics *(*fake_BlockGraphics_BlockGraphics)(BlockGraphics *, std::string const &);

extern BlockGraphics *(*fake_BlockGraphics_lookupByName)(std::string const &, bool);

extern Block *(*fake_BlockGraphics_getBlock)(BlockGraphics *);

extern BlockGraphics *(*fake_BlockGraphics_setDefaultCarriedTextures)(BlockGraphics *);

extern std::unordered_map<unsigned int,BlockGraphics *> (*fake_BlockGraphics_mBlocks);

extern std::unordered_map<std::string ,BlockGraphics *> (*fake_BlockGraphics_mBlockLookupMap);

extern std::vector<std::unique_ptr<BlockGraphics>> (*fake_BlockGraphics_mOwnedBlocks);

extern BlockGraphics *(*fake_BlockGraphics_setCarriedTextures)(BlockGraphics *,std::string const &);

//_ZN13BlockGraphics21setCarriedTextureItemERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE
//hook区
extern BlockGraphics *(*base_BlockGraphics_registerBlockGraphics)(std::vector<Json::Value> &, std::string const &, BlockShape);
extern BlockGraphics * NC_BlockGraphics_registerBlockGraphics(std::vector<Json::Value> & , std::string const & , BlockShape );
extern void (*base_BlockGraphics_initBlocks)(BlockGraphics *, ResourcePackManager &, Experiments const &);

extern void NC_BlockGraphics_initBlocks(BlockGraphics *, ResourcePackManager &, Experiments const &);

extern BlockGraphics *(*base_BlockGraphics_BlockGraphics)(BlockGraphics *, std::string const &);

extern BlockGraphics *NC_BlockGraphics_BlockGraphics(BlockGraphics *, std::string const &);

extern BlockGraphics *(*base_BlockGraphics_setTextureItem)(BlockGraphics *, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &);

extern BlockGraphics *NC_BlockGraphics_setTextureItem(BlockGraphics *, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &, std::string const &);


extern BlockGraphics *(*base_BlockGraphics_lookupByName)(std::string const &, bool);

extern BlockGraphics *NC_BlockGraphics_lookupByName(std::string const &, bool);

extern void (*base_BlockGraphics_registerLooseBlockGraphics)(std::vector<Json::Value> &);

extern void NC_BlockGraphics_registerLooseBlockGraphics(std::vector<Json::Value> &);
//_ZN13BlockGraphics26registerLooseBlockGraphicsERNSt6__ndk16vectorIN4Json5ValueENS0_9allocatorIS3_EEEE
#endif //MCENGINE_FAKE_BLOCKGRAPHICS_HPP
