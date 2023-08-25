//
// Created by 30225 on 2023/8/23.
//

#ifndef MCENGINE_FAKE_BLOCKTYPEREGISTRY_HPP
#define MCENGINE_FAKE_BLOCKTYPEREGISTRY_HPP


#include "Fake_Material.hpp"
#include "Fake_BlockLegacy.hpp"
#include "sharedptr.h"

class BlockTypeRegistry
{

};
//fake区
extern BlockLegacy * (*fake_BlockTypeRegistry_registerBlock)(std::string const&,int *,Material const&);
//_ZN17BlockTypeRegistry13registerBlockI11BlockLegacyJRA14_KciRK8MaterialEEERT_DpOT0_
//hook区
extern BlockLegacy * (*base_BlockTypeRegistry_registerBlock)(std::string const&,int *,Material const&);
extern BlockLegacy * NC_BlockTypeRegistry_registerBlock(std::string const&,int *,Material const&);
#endif //MCENGINE_FAKE_BLOCKTYPEREGISTRY_HPP
