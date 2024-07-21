//
// Created by 25843 on 2023/10/14.
//

#ifndef MCENGINE_ITEMINSTANCEFAKER_HPP
#define MCENGINE_ITEMINSTANCEFAKER_HPP


#include "ItemStackBaseFaker.hpp"
#include "BlockLegacyFaker.hpp"
#include "../../includes/tools/gsl/gsl"

static ItemInstance* (*fake_ItemInstance_Item)(Item const&);

#endif //MCENGINE_ITEMINSTANCEFAKER_HPP
