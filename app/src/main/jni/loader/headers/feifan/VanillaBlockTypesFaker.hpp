//
// Created by 30225 on 2023/8/23.
//

#ifndef MCENGINE_VANILLABLOCKTYPESFAKER_HPP
#define MCENGINE_VANILLABLOCKTYPESFAKER_HPP

#include "BlockLegacyFaker.hpp"

class Experiments;
class VanillaBlockTypes
{

};
//fake区

//hook区
extern void (*base_VanillaBlockTypes_registerBlocks)(VanillaBlockTypes *, Experiments const &);

extern void NC_VanillaBlockTypes_registerBlocks(VanillaBlockTypes *, Experiments const &);

//_ZN17VanillaBlockTypes14registerBlocksERK11Experiments
#endif //MCENGINE_VANILLABLOCKTYPESFAKER_HPP
