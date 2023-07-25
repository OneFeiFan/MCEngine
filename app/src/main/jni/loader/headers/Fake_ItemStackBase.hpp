#ifndef EX_FAKE_ITEMSTACKBASE_HPP
#define EX_FAKE_ITEMSTACKBASE_HPP
#include <dlfcn.h>
class Item;
class ItemStackBase
{
public:
	Item *item;
	ItemStackBase(Item const &, int, int);
	int getAuxValue() const;
	int getIdAux() const;
	void setAuxValue(short);
	Item *getItem() const;
};//
static short (*fake_ItemStackBase_getId)(ItemStackBase *);
#endif