//
// Created by 25843 on 2024/7/21.
//

#ifndef MCENGINE_ITEMSTACK_H
#define MCENGINE_ITEMSTACK_H

#include "BlockLegacy.h"
#include "../../includes/tools/gsl/gsl"

class Mob;
class Level;
class CompoundTag;
class Player;
class Item;
class ItemInstance;
class RecipeIngredient;
class Actor;
class Block;

class ItemStack {
public:
    //Virtual Tables
    virtual ~ItemStack();
    virtual void reinit(Item const&, int, int);
    virtual void reinit(BlockLegacy const&, int);
    virtual void reinit(gsl::basic_string_span<char const, 1>, int, int);
    virtual void setNull();
    virtual void toString() const;
    virtual void toDebugString() const;
public:
    //Methods
    ItemStack(ItemInstance const&);
    ItemStack(Block const&, int, CompoundTag const*);
    ItemStack(ItemStack const&);
    ItemStack(Item const&, int);
    ItemStack(Item const&, int, int);
    ItemStack(BlockLegacy const&, int);
    ItemStack(gsl::basic_string_span<char const, 1>, int, int, CompoundTag const*);
    ItemStack(Item const&, int, int, CompoundTag const*);
    ItemStack(Item const&);
    ItemStack(RecipeIngredient const&);
    ItemStack();
    void tryGetItemStackNetId() const;
    void fromTag(CompoundTag const&, Level&);
    void fromTag(CompoundTag const&);
    //void serverInitRequestId(TypedClientNetId<ItemStackRequestIdTag, int, 0> const&);
    void matchesNetIdVariant(ItemStack const&) const;
    //void clientInitLegacyRequestId(TypedClientNetId<ItemStackLegacyRequestIdTag, int, 0> const&);
    void hasItemStackNetId() const;
    void getMaxUseDuration() const;
    void releaseUsing(Player*, int);
    void _assignNetIdVariant(ItemStack const&) const;
    void hasClientRequestId() const;
    void tryGetLegacyRequestId() const;
    void removeEnchants();
    //void clientInitRequestId(TypedClientNetId<ItemStackRequestIdTag, int, 0> const&);
    void serverInitNetId();
    void useOn(Actor&, int, int, int, unsigned char, float, float, float);
    void mineBlock(Block const&, int, int, int, Mob*);
    void sameItemAndAuxAndBlockData(ItemStack const&) const;
    void getItemStackNetIdVariant() const;
    void getLightEmission() const;
    void hasLegacyClientRequestId() const;
    void playSoundIncrementally(Mob&) const;
    void operator=(ItemStack const&);
    void use(Player&);
    void clone() const;
    void getStrippedNetworkItem() const;
    void useAsFuel();
    void getDestroySpeed(Block const&) const;
    //void clientInitNetId(TypedServerNetId<ItemStackNetIdTag, int, 0> const&);
    void useTimeDepleted(Level*, Player*);
    void matchesAndNetIdVariantMatches(ItemStack const&) const;
    void tryGetItemStackRequestId() const;
    void inventoryTick(Level&, Actor&, int, bool);
public:
    //Objects
    static ItemStack * EMPTY_ITEM;
};//ItemStack

#endif //MCENGINE_ITEMSTACK_H
