#ifndef EX_FAKE_ITEMSTACKBASE_HPP
#define EX_FAKE_ITEMSTACKBASE_HPP

#include <dlfcn.h>
#include "Fake_HashedString.h"
#include "./includes/gsl/gsl"
#include "Fake_Actor.hpp"
#include "Fake_BlockSource.hpp"
#include "../includes/lib_json/json/json.h"

class Item;
class CompoundTag;
class RecipeIngredient;
class RenderParams;
class VariantParameterList;
class ItemEnchants;
class Level;
class BlockActor;
class Player;
class BinaryStream;
class ItemInstance;
class Tick;
class ReadOnlyBinaryStream;
class IDataInput;
class IDataOutput;
class Actor;

class ItemStackBase {
public:
    //Virtual Tables
    virtual ~ItemStackBase();
    //pure virtual method
    //pure virtual method
    //pure virtual method
    virtual void setNull();
    virtual void toString() const;
    virtual void toDebugString() const;
public:
    //Methods
    ItemStackBase(Block const&, int, CompoundTag const*);
    ItemStackBase(BlockLegacy const&, int, short);
    ItemStackBase(ItemStackBase const&);
    ItemStackBase(Item const&);
    ItemStackBase(Item const&, int, int);
    ItemStackBase(Item const&, int, int, CompoundTag const*);
    ItemStackBase();
    ItemStackBase(Item const&, int);
    ItemStackBase(gsl::basic_string_span<char const, 1>, int, int, CompoundTag const*);
    ItemStackBase(BlockLegacy const&, int);
    ItemStackBase(RecipeIngredient const&);
    void isInstance(HashedString const&, bool) const;
    void getMaxDamage() const;
    void getWasPickedUp() const;
    void shouldVanish() const;
    void initParams(RenderParams&, Actor*);
    void isBlock() const;
    void isLiquidClipItem() const;
    void isFullStack() const;
    void getBlock() const;
    void setBlock(Block const*);
    void getLegacyBlock() const;
    void getIdAux() const;
    void set(int);
    void getArmorSlot() const;
    void getRawNameHash() const;
    void remove(int);
    void shouldInteractionWithBlockBypassLiquid(Block const&) const;
    void save() const;
    void setPickupTime(std::__ndk1::chrono::time_point<std::__ndk1::chrono::steady_clock, std::__ndk1::chrono::duration<long long, std::__ndk1::ratio<1ll, 1000000000ll> > >);
    void setJustBrewed(bool);
    void isGlint() const;
    void isOneOfInstances(std::__ndk1::vector<HashedString, std::__ndk1::allocator<HashedString> >, bool) const;
    void isExplodable() const;
    void getItem() const;
    void setUserData(std::__ndk1::unique_ptr<CompoundTag, std::__ndk1::default_delete<CompoundTag> >);
    void initParams(VariantParameterList&, Actor*);
    void getAttackDamage() const;
    void saveEnchantsToUserData(ItemEnchants const&);
    void constructItemEnchantsFromUserData() const;
    void _makeChargedItemFromUserData();
    void _initComponents();
    void setDamageValue(short);
    void refreshedInContainer(Level&) const;
    void wasJustBrewed() const;
    void isPattern() const;
    void isPotionItem() const;
    void sameItemAndAux(ItemStackBase const&) const;
    void getPickupTime() const;
    void isHorseArmorItem() const;
    void load(CompoundTag const&);
    void getUseAnimation() const;
    void getComponentItem() const;
    void canBeCharged() const;
    void _saveComponents(CompoundTag&) const;
    void getMaxStackSize() const;
    void getIdAuxEnchanted() const;
    void operator==(ItemStackBase const&) const;
    void setCustomName(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    void getRawNameId() const;
    void addCustomUserData(BlockActor&, BlockSource&);
    void hasSameUserData(CompoundTag const*) const;
    void isOffhandItem() const;
    void isInstance(BlockLegacy const&) const;
    void init(BlockLegacy const&, int);
    void isNull() const;
    void getDescriptionId() const;
    void clearChargedItem();
    void componentsMatch(ItemStackBase const&) const;
    void getBlockingTick() const;
    void matchesItem(ItemStackBase const&) const;
    void resetHoverName();
    void isDamageableItem() const;
    void isStackable(ItemStackBase const&) const;
    void hasCustomHoverName() const;
    void getHoverName() const;
    void hasChargedItem() const;
    void _loadComponents(CompoundTag const&);
    void setCustomLore(std::__ndk1::vector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::allocator<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > > > const&);
    void getCustomName() const;
    void init(int, int, int, bool);
    void startCoolDown(Player*) const;
    void setWasPickedUp(bool);
    void getAuxValue() const;
    void setShowPickUp(bool);
    void add(int);
    void hasCompoundTextUserData() const;
    void getIcon(int, bool) const;
    void isFireResistant() const;
    void _cloneComponents(ItemStackBase const&);
    void hasSameAuxValue(ItemStackBase const&) const;
    void init(Item const&, int, int, CompoundTag const*, bool);
    void setAuxValue(short);
    void retrieveAuxValFromIDAux(int);
    void hasSameUserData(ItemStackBase const&) const;
    void canDestroySpecial(Block const&) const;
    void _write(BinaryStream&) const;
    void getColor() const;
    void getNetworkUserData() const;
    void updateComponent(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, Json::Value const&);
    void hasTag(HashedString const&) const;
    void isThrowable() const;
    void setChargedItem(ItemInstance const&, bool);
    void load(CompoundTag const&, Level&);
    void _getHoverFormattingPrefix() const;
    void retrieveEnchantFromIDAux(int);
    void showsDurabilityInCreative() const;
    void getEnchantSlot() const;
    void snap(Player*);
    void getChargedItem() const;
    void operator=(ItemStackBase const&);
    void setStackSize(unsigned char);
    void initClient(Json::Value&);
    void isValidAuxValue(int) const;
    void setBlockingTick(Tick);
    void isUseable() const;
    void _isInstance(gsl::basic_string_span<char const, 1>) const;
    void isDamaged() const;
    void getId() const;
    void sameItem(ItemStackBase const&) const;
    void _hasComponents() const;
    void getUserData() const;
    void _isVanillaItemInstance(HashedString const&) const;
    void _checkForItemWorldCompatibility();
    void getName() const;
    void _read(ReadOnlyBinaryStream&);
    void getIsValidPickupTime() const;
    void matchesChargedItem(ItemStackBase const&) const;
    void operator!=(ItemStackBase const&) const;
    void hurtAndBreak(int, Actor*);
    void getEffectName() const;
    void isEquivalentArmor(ItemStackBase const&) const;
    void isArmorItem() const;
    void hasSameUserDataExcept(ItemStackBase const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&) const;
    void sendItemDefinitionEventTriggered(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    void getUserData();
    void setRepairCost(int);
    void canPlaceOn(Block const*) const;
    void isStackedByData() const;
    void sameItem(int, int) const;
    void hasComponent(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&) const;
    void getDescriptor() const;
    void getDamageValue() const;
    void isMusicDiscItem() const;
    void hasTag(unsigned long long const&) const;
    void _setItem(int, bool);
    void deserializeComponents(IDataInput&);
    void getCustomLore() const;
    void getFormattedHovertext(Level&, bool) const;
    void addComponents(Json::Value const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >&);
    void isValidComponent(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    void isEnchantingBook() const;
    void _loadItem(CompoundTag const&);
    void isWearableItem() const;
    void setPickupTime();
    void getPickupPopPercentage() const;
    void isEnchanted() const;
    void getBaseRepairCost() const;
    void hasUserData() const;
    void _setChargedItem(ItemInstance const&);
    void getCategoryName() const;
    void getEnchantValue() const;
    void isStackable() const;
    void matches(ItemStackBase const&) const;
    void getRendererId() const;
    void retrieveIDFromIDAux(int);
    void canDestroy(Block const*) const;
    void _updateCompareHashes();
    void matchesEitherWearableCase(CompoundTag const*) const;
    void serializeComponents(IDataOutput&) const;
    void hasFeedingAnimation() const;
    void getRequiredBaseGameVersion() const;
public:
    //Objects
    static ItemStackBase * TAG_LORE;
    static ItemStackBase * TAG_CAN_PLACE_ON;
    static ItemStackBase * TAG_STORE_CAN_PLACE_ON;
    static ItemStackBase * TAG_DISPLAY;
    static ItemStackBase * TAG_DISPLAY_NAME;
    static ItemStackBase * TAG_ENCHANTS;
    static ItemStackBase * TAG_CAN_DESTROY;
    static ItemStackBase * TAG_CHARGED_ITEM;
    static ItemStackBase * TAG_REPAIR_COST;
    static ItemStackBase * MAX_STACK_SIZE;
    static ItemStackBase * TAG_STORE_CAN_DESTROY;
};

//ItemStackBase

static short (*fake_ItemStackBase_getId)(ItemStackBase *);
#endif