#ifndef EX_ITEMSTACK_H
#define EX_ITEMSTACK_H

#include "Fake_ItemStackBase.hpp"
class Item;
class ItemStack : public ItemStackBase {
    public:
	ItemStack(Item const&);
	ItemStack(Item const&, int);
	ItemStack(Item const&, int,int);
	ItemStack();
};
#endif