//
// Created by 30225 on 2023/8/23.
//

#ifndef MCENGINE_FAKE_BLOCKTYPEREGISTRY_HPP
#define MCENGINE_FAKE_BLOCKTYPEREGISTRY_HPP


#include "Fake_Material.hpp"
#include "Fake_BlockLegacy.hpp"
#include "sharedptr.h"
#include <map>
#include <unordered_map>
class BlockTypeRegistry
{

};
//fake区
extern BlockLegacy * (*fake_BlockTypeRegistry_registerBlock)(std::string const&,int *,Material const&);
extern WeakPtr<BlockLegacy> (*fake_BlockTypeRegistry_lookupByName)(std::string const&,bool);
extern  std::unordered_map<std::string,SharedPtr<BlockLegacy>> *(*fake_BlockTypeRegistry_mBlockLookupMap);

//std::unordered_map<std::string,SharedPtr<BlockLegacy>>
//hook区
extern BlockLegacy * (*base_BlockTypeRegistry_registerBlock)(std::string const&,int *,Material const&);
extern BlockLegacy * NC_BlockTypeRegistry_registerBlock(std::string const&,int *,Material const&);

extern WeakPtr<BlockLegacy> (*base_BlockTypeRegistry_lookupByName)(std::string const&,bool);
extern WeakPtr<BlockLegacy> NC_BlockTypeRegistry_lookupByName(std::string const&,bool);
#endif //MCENGINE_FAKE_BLOCKTYPEREGISTRY_HPP
