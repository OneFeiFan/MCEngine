//
// Created by 30225 on 2023/8/23.
//

#include <iostream>
#include "../headers/feifan/BlockTypeRegistryFaker.hpp"

BlockLegacy *(*fake_BlockTypeRegistry_registerBlock)(std::string const &, int *, Material const &);

WeakPtr<BlockLegacy> (*fake_BlockTypeRegistry_lookupByName)(std::string const &, bool);

std::unordered_map<std::string, SharedPtr<BlockLegacy>> *(*fake_BlockTypeRegistry_mBlockLookupMap);

//hook区
BlockLegacy *(*base_BlockTypeRegistry_registerBlock)(std::string const &, int *, Material const &);

BlockLegacy *NC_BlockTypeRegistry_registerBlock(std::string const &str, int *a, Material const &b)
{
    return base_BlockTypeRegistry_registerBlock(str, a, b);
}