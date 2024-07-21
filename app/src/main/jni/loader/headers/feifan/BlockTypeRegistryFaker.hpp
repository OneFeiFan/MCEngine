//
// Created by 30225 on 2023/8/23.
//

#ifndef MCENGINE_BLOCKTYPEREGISTRYFAKER_HPP
#define MCENGINE_BLOCKTYPEREGISTRYFAKER_HPP


#include "MaterialFaker.hpp"
#include "BlockLegacyFaker.hpp"
#include "../mojang/sharedptr.h"
#include <map>
#include <unordered_map>

class BlockTypeRegistry
{

};

//fake区
extern BlockLegacy *(*fake_BlockTypeRegistry_registerBlock)(std::string const &, int *, Material const &);

extern WeakPtr<BlockLegacy> (*fake_BlockTypeRegistry_lookupByName)(std::string const &, bool);

extern std::unordered_map<std::string, SharedPtr<BlockLegacy>> *(*fake_BlockTypeRegistry_mBlockLookupMap);

//std::unordered_map<std::string,SharedPtr<BlockLegacy>>
//hook区
extern BlockLegacy *(*base_BlockTypeRegistry_registerBlock)(std::string const &, int *, Material const &);

extern BlockLegacy *NC_BlockTypeRegistry_registerBlock(std::string const &, int *, Material const &);

#endif //MCENGINE_BLOCKTYPEREGISTRYFAKER_HPP
