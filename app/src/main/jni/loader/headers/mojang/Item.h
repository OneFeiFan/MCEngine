//
// Created by 25843 on 2024/7/21.
//

#ifndef MCENGINE_ITEM_H
#define MCENGINE_ITEM_H
#include <string>

class HashedString;
class ItemStack;
class Actor;
class ItemInstance;
class TextureUVCoordinateSet{};
class ItemStackBase;

class Item
{
public:
    class Tier
    {
    private:
        const int mLevel;
        const int mDurability;
        const float mSpeed;
        const int mDamage;
        const int mEnchantmentValue;
    public:
        Tier(int level, int durability, float speed, int damage, int echantmentValue);
    };

public:
    // Virtual Tables
    virtual ~Item();

    // virtual ~Item();
    //
    // virtual void tearDown();
    // virtual void getMaxUseDuration(ItemInstance const*) const;
    // virtual void getMaxUseDuration(ItemStack const*) const;
    virtual bool isMusicDisk() const;
    // virtual void executeEvent(ItemStackBase&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, RenderParams&) const;
    virtual bool isComponentBased() const;
    virtual bool isArmor() const;
    virtual bool isBlockPlanterItem() const;
    virtual bool isBucket() const;
    virtual bool isCamera() const;
    virtual bool isDamageable() const;
    virtual bool isDyeable() const;
    virtual bool isDye() const;
    virtual void getItemColor() const;
    virtual bool isFertilizer() const;
    virtual bool isFood() const;
    virtual bool isThrowable() const;
    virtual bool isUseable() const;
    // virtual void getCamera() const;
    // virtual void getFood() const;
    // virtual void getFuel() const;

    // virtual void setStackedByData(bool);
    // virtual void setHandEquipped();
    // virtual void setUseAnimation(UseAnimation);
    // virtual void setMaxUseDuration(int);
    // virtual void setRequiresWorldBuilder(bool);
    // virtual void setExplodable(bool);
    // virtual void setFireResistant(bool);
    // virtual void setIsGlint(bool);
    // virtual void setShouldDespawn(bool);
    // virtual void getBlockShape() const;
    // virtual void canBeDepleted() const;
    // virtual void canDestroySpecial(Block const&) const;
    // virtual void getLevelDataForAuxValue(int) const;
    // virtual void isStackedByData() const;
    // virtual void getMaxDamage() const;
    // virtual void getAttackDamage() const;
    // virtual void isHandEquipped() const;
    // virtual void isGlint(ItemStackBase const&) const;
    // virtual void isPattern() const;
    // virtual void getPatternIndex() const;
    // virtual void showsDurabilityInCreative() const;
    // virtual void isWearableThroughLootTable(CompoundTag const*) const;
    // virtual void canDestroyInCreative() const;
    // virtual void isDestructive(int) const;
    // virtual void isLiquidClipItem(int) const;
    // virtual void shouldInteractionWithBlockBypassLiquid(Block const&) const;
    // virtual void requiresInteract() const;
    // virtual void appendFormattedHovertext(ItemStackBase const&, Level&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >&, bool) const;
    // virtual void isValidRepairItem(ItemStackBase const&, ItemStackBase const&) const;
    // virtual void getEnchantSlot() const;
    // virtual void getEnchantValue() const;
    // virtual void getArmorValue() const;
    // virtual void isComplex() const;
    // virtual void isValidAuxValue(int) const;
    // virtual void getDamageChance(int) const;
    // virtual void uniqueAuxValues() const;
    // virtual void isActorPlacerItem() const;
    // virtual void isMultiColorTinted(ItemStack const&) const;
    // virtual void getColor(CompoundTag const*, ItemDescriptor const&) const;
    // virtual void hasCustomColor(ItemStackBase const&) const;
    // virtual void hasCustomColor(CompoundTag const*) const;
    // virtual void clearColor(ItemStackBase&) const;
    // virtual void clearColor(CompoundTag*) const;
    // virtual void setColor(ItemStackBase&, mce::Color const&) const;
    // virtual void getBaseColor(ItemStack const&) const;
    // virtual void getSecondaryColor(ItemStack const&) const;
    // virtual void getActorIdentifier(ItemStack const&) const;
    // virtual void saveAdditionalData(ItemStackBase const&, CompoundTag&) const;
    // virtual void readAdditionalData(ItemStackBase&, CompoundTag const&) const;
    // virtual void buildIdAux(short, CompoundTag const*) const;
    // virtual void buildDescriptor(short, CompoundTag const*) const;
    // virtual void use(ItemStack&, Player&) const;
    // virtual void dispense(BlockSource&, Container&, int, Vec3 const&, unsigned char) const;
    // virtual void useTimeDepleted(ItemStack&, Level*, Player*) const;
    // virtual void releaseUsing(ItemStack&, Player*, int) const;
    // virtual void getDestroySpeed(ItemStackBase const&, Block const&) const;
    // virtual void hurtActor(ItemStack&, Actor&, Mob&) const;
    // virtual void hitActor(ItemStack&, Actor&, Mob&) const;
    // virtual void hitBlock(ItemStack&, Block const&, BlockPos const&, Mob&) const;
    // virtual void mineBlock(ItemInstance&, Block const&, int, int, int, Actor*) const;
    // virtual void mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
    // virtual void buildDescriptionName(ItemStackBase const&) const;
    // virtual void buildDescriptionId(ItemDescriptor const&, CompoundTag const*) const;
    // virtual void buildEffectDescriptionName(ItemStackBase const&) const;
    // virtual void buildCategoryDescriptionName() const;
    // virtual void readUserData(ItemStackBase&, IDataInput&, ReadOnlyBinaryStream&) const;
    // virtual void writeUserData(ItemStackBase const&, IDataOutput&) const;
    // virtual void getMaxStackSize(ItemDescriptor const&) const;
    // virtual void inventoryTick(ItemStack&, Level&, Actor&, int, bool) const;
    // virtual void refreshedInContainer(ItemStackBase const&, Level&) const;
    // virtual void getCooldownType() const;
    // virtual void getCooldownTime() const;
    // virtual void fixupCommon(ItemStackBase&) const;
    // virtual void fixupCommon(ItemStackBase&, Level&) const;
    // virtual void getDamageValue(CompoundTag const*) const;
    // virtual void setDamageValue(ItemStackBase&, short) const;
    // virtual void getInHandUpdateType(Player const&, ItemInstance const&, ItemInstance const&, bool, bool) const;
    // virtual void getInHandUpdateType(Player const&, ItemStack const&, ItemStack const&, bool, bool) const;
    // virtual void validFishInteraction(int) const;
    // virtual void isSameItem(ItemStackBase const&, ItemStackBase const&) const;
    // virtual void initClient(Json::Value&, Json::Value&);
    // virtual void getInteractText(Player const&) const;
    // virtual void getAnimationFrameFor(Mob*, bool, ItemStack const*, bool) const;
    // virtual void isEmissive(int) const;
    // virtual void getLightEmission(int) const;
    // virtual void getIcon(ItemStackBase const&, int, bool) const;
    // virtual void getIconYOffset() const;
    virtual void setIcon(std::string const &, int);

    virtual void setIcon(TextureUVCoordinateSet const &);
    // virtual void setIconAtlas(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, int);
    // virtual void canBeCharged() const;
    // virtual void playSoundIncrementally(ItemInstance const&, Mob&) const;
    // virtual void playSoundIncrementally(ItemStack const&, Mob&) const;
    // virtual void getFurnaceBurnIntervalMultipler(ItemStackBase const&) const;
    // virtual void getFurnaceXPmultiplier(ItemStackBase const&) const;
    // virtual void getAuxValuesDescription() const;
    // virtual void _checkUseOnPermissions(Actor&, ItemStackBase&, unsigned char const&, BlockPos const&) const;
    // virtual void _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;
    // virtual void _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
public:
    // Methods
    //  void setIsMirroredArt(bool);
    //  void resetId(short);

    //  void getFrameCount() const;
    void setCreativeGroup(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    void reloadIcon();
    //  void getFullNameHash() const;
    //  void allowOffhand() const;
    //  void beginCreativeGroup(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, ItemInstance const&);
    void addCreativeItem(ItemInstance const &);

    //  void _addLooseCreativeItemsClient();
    //  void getDescriptionId() const;
    static void addCreativeItem(Item *, short);

    //  void fixupOnLoad(ItemStackBase&) const;
    //  void isAnimatedInToolbar() const;
    //  void startCreativeItemDefinitions(bool, CreativeItemRegistry*);
    //  void getRenderingScaleAdjustment() const;
    //  void getIconTextureUVSet(TextureAtlasItem const&, int, int);
    void useOn(ItemStack &, Actor &, int, int, int, unsigned char, float, float, float) const;

    // void getRenderingRotAdjustment() const;
    // void addOnResetBAIcallback(std::__ndk1::function<void ()> const&);
    // void usesRenderingAdjustment() const;
    // void isNameTag() const;
    // void canUseSeed(Actor&, BlockPos, unsigned char) const;
    // void isFlyEnabled(ItemInstance const&);
    // void getIconTexture() const;
    // void toBlockId(short);
    // void fixupOnLoad(ItemStackBase&, Level&) const;
    // void getTextureItem(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    // void getTextureUVCoordinateSet(std::string const&, int);
    // void setDescriptionId(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    // void getCreativeGroup() const;
    Item *setCategory(CreativeItemCategory);

    // void destroySpeedBonus(ItemStackBase const&) const;
    // void executeOnResetBAIcallbacks() const;
    // void setMinRequiredBaseGameVersion(BaseGameVersion const&);
    // void addLooseCreativeItems(bool, BaseGameVersion const&);
    // void setFurnaceBurnIntervalMultiplier(float);
    // void shouldDespawn() const;
    // void _tryCorrectAnyAuxValue(ItemStackBase&) const;
    // void beginCreativeGroup(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, Block const*, CompoundTag const*);
    // void isElytra(ItemDescriptor const&);
    // void getSeed() const;
    // void isExplodable() const;
    // void getUseAnimation() const;
    // void hasTag(unsigned long long const&) const;
    // void alterAvailableCreativeItems(ActorInfoRegistry*, LevelData&);
    // void getCreativeCategory() const;
    // void getLegacyBlock() const;
    bool isSeed() const;
    // void isElytraBroken(int);
    // void isMirroredArt() const;
    // void getRenderingPosAdjustment() const;
    // void getRawNameHash() const;
    // void getRawNameId() const;
    // void getRequiredBaseGameVersion() const;
    // void setFurnaceXPmultiplier(float);
    // void _addLooseCreativeItemsServer(BaseGameVersion const&);
    // void endCreativeGroup();
    // void ignoresPermissions() const;
    char *getFullItemName() const;

    // void setAllowOffhand(bool);
    // void endCreativeItemDefinitions(bool);
    // void isFireResistant() const;
    // void _textMatch(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, bool);
    // void getSerializedName() const;
    // void getNamespace() const;

    // void setAtlasItemManager(std::__ndk1::shared_ptr<AtlasItemManager>);
    // void beginCreativeGroup(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, Item*, short, CompoundTag const*);
    void addCreativeItem(ItemStack const &);

    short getId() const;
    // void updateCustomBlockEntityTag(BlockSource&, ItemStackBase&, BlockPos const&) const;
    // void addCreativeItem(Block const&);
    // void hasTag(HashedString const&) const;
    // void isElytra() const;
    // void getRendererId() const;
    // void beginCreativeGroup(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, short, short, CompoundTag const*);
    // void _helpChangeInventoryItemInPlace(Actor&, ItemStack&, ItemStack&, ItemAcquisitionMethod) const;
public:
    // Objects
    static Item *mItemTextureItems;
    static Item *mActiveCreativeItemCategory;
    static Item *mServerItemsUsedInCreativeItems;
    static Item *ICON_DESCRIPTION_PREFIX;
    static Item *mActiveCreativeItemRegistry;
    static Item *mInvalidTextureUVCoordinateSet;
    static Item *TAG_DAMAGE;
    static Item *mGenerateDenyParticleEffect;
    static Item *mActiveCreativeGroupInfo;
};
#endif //MCENGINE_ITEM_H
