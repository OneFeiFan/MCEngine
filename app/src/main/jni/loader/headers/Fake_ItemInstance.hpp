//
// Created by 25843 on 2023/10/14.
//

#ifndef MCENGINE_FAKE_ITEMINSTANCE_HPP
#define MCENGINE_FAKE_ITEMINSTANCE_HPP


#include "Fake_ItemStackBase.hpp"
#include "Fake_BlockLegacy.hpp"
#include "../includes/gsl/gsl"

class ItemInstance : public ItemStackBase {

public:
    //Virtual Tables
    virtual ~ItemInstance();
    virtual void reinit(Item const&, int, int);
    virtual void reinit(BlockLegacy const&, int);
    virtual void reinit(gsl::basic_string_span<char const, 1>, int, int);
public:
    //Methods
    ItemInstance(Item const&, int);
    ItemInstance(ItemStackBase const&);
    ItemInstance(Item const&, int, int);
    ItemInstance(ItemInstance const&);
    ItemInstance(gsl::basic_string_span<char const, 1>, int, int, CompoundTag const*);
    ItemInstance(Item const&, int, int, CompoundTag const*);
    ItemInstance(BlockLegacy const&, int);
    ItemInstance(BlockLegacy const&, int, short);
    ItemInstance();
    ItemInstance(Block const&, int, CompoundTag const*);
    ItemInstance(Item const&);
    void clone() const;
    void fromTag(CompoundTag const&);
    void operator=(ItemInstance const&);
public:
    //Objects
    static ItemInstance * EMPTY_ITEM;
};//ItemInstance

static ItemInstance* (*fake_ItemInstance_Item)(Item const&);

#endif //MCENGINE_FAKE_ITEMINSTANCE_HPP
