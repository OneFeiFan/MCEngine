#ifndef EX_BLOCK_H
#define EX_BLOCK_H

//This header template file is generated by Disassembler.
class BlockSource;
class BlockPos;
class Block {
public:
    //Fields
    //char filler_Block[UNKNOW_SIZE];
public:
    //Virtual Tables
	virtual ~Block();
	//virtual ~Block();
	virtual void getRenderLayer() const;
public:
    //Methods
    // Block(unsigned short, gsl::not_null<BlockLegacy*>);
    // Block(unsigned short, gsl::not_null<BlockLegacy*>, CompoundTag, unsigned int const&);
    // void hasRuntimeId() const;
    // void ignoreEntitiesOnPistonMove() const;
    // void getDirectSignal(BlockSource&, BlockPos const&, int) const;
    // void isBounceBlock() const;
    // void transformOnFall(BlockSource&, BlockPos const&, Actor*, float) const;
    // void tryToPlace(BlockSource&, BlockPos const&, ActorBlockSyncMessage const*) const;
    // void getBurnOdds() const;
    // void canProvideSupport(unsigned char, BlockSupportType) const;
    // void getSilkTouchItemInstance() const;
    // void getCreativeCategory() const;
    // void isSolidBlockingBlock() const;
    // void addAABB(AABB const&, AABB const*, std::__ndk1::vector<AABB, std::__ndk1::allocator<AABB> >&) const;
    // void isContainerBlock() const;
    // void canSlide(BlockSource&, BlockPos const&) const;
    // void canBeFertilized(BlockSource&, BlockPos const&, Block const&) const;
    // void dealsContactDamage(Actor const&, bool) const;
    // void isAuxValueRelevantForPicking() const;
    // void hasState(ItemState const&) const;
    // void executeItemEvent(ItemStackBase&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, BlockSource&, BlockPos const&, Actor*) const;
    // void isButtonBlock() const;
    // void getLiquidClipVolume(BlockSource&, BlockPos const&, AABB&) const;
    // void getExperienceDrop(Random&) const;
    // void hasTag(unsigned long long const&) const;
    // void ignoreBlockForInsideCubeRenderer() const;
    // void setupRedstoneComponent(BlockSource&, BlockPos const&) const;
    // void isFenceGateBlock() const;
    // void shouldDispense(BlockSource&, Container&) const;
    // void tickInternal(BlockSource&, BlockPos const&, Random&) const;
    // void setRuntimeId(unsigned int const&) const;
    // void handleRain(BlockSource&, BlockPos const&, float) const;
    // void isMotionBlockingBlock() const;
    // void buildSerializationId(unsigned int);
    // void isSignalSource() const;
    // void getGravity() const;
    // void getVisualShapeInWorld(BlockSource&, BlockPos const&, AABB&, bool) const;
    // void getUIShape(AABB&) const;
    // void getRenderLayer(BlockSource&, BlockPos const&) const;
    // void hasTag(HashedString const&) const;
    // void onFertilized(BlockSource&, BlockPos const&, Actor*, FertilizerType) const;
    // void shouldRandomTick() const;
    // void getMaterial() const;
    // void triggerEvent(BlockSource&, BlockPos const&, int, int) const;
    // void isDoor() const;
    // void canBeSilkTouched() const;
    // void getStrippedBlock() const;
    // void getRawNameId() const;
    // void shouldConnectToRedstone(BlockSource&, BlockPos const&, int) const;
    // void sanitizeFillBlock(BlockSource&, BlockPos const&, Block const&) const;
    // void matchesStates(BlockLegacy const&) const;
    // void isStairBlock() const;
    // void canInstatick() const;
    // void getExtraRenderLayers() const;
    // void dispense(BlockSource&, Container&, int, Vec3 const&, unsigned char) const;
    // void onStepOff(Actor&, BlockPos const&) const;
    // void onMove(BlockSource&, BlockPos const&, BlockPos const&) const;
    // void isCraftingBlock() const;
    // void telemetryVariant(BlockSource&, BlockPos const&) const;
    // void animateTick(BlockSource&, BlockPos const&, Random&) const;
    // void use(Player&, BlockPos const&, unsigned char) const;
    // void buildDescriptionName() const;
    // void getDescriptionId() const;
    // void getCollisionShape(AABB&, BlockSource&, BlockPos const&, Actor*) const;
    // void isCropBlock() const;
    // void isTrapdoor() const;
    // void onStandOn(Actor&, BlockPos const&) const;
    // void trySpawnResourcesOnExplosion(BlockSource&, BlockPos const&, Block const&, std::__ndk1::vector<Item const*, std::__ndk1::allocator<Item const*> >*, float, int, bool) const;
    // void isUnbreakable() const;
    // void waterSpreadCausesSpawn() const;
    // void DEPRECATEDcallOnGraphicsModeChanged(BlockGraphicsModeChangeContext const&);
    // void isSlabBlock() const;
    // void isFenceBlock() const;
    // void operator==(Block const&) const;
    // void executeTrigger(DefinitionTrigger const&, RenderParams&) const;
    // void getComparatorSignal(BlockSource&, BlockPos const&, unsigned char) const;
    // void hasComparatorSignal() const;
    // void queuedTick(BlockSource&, BlockPos const&, Random&) const;
    // void onStepOn(Actor&, BlockPos const&) const;
    // void getOutline(BlockSource&, BlockPos const&, AABB&) const;
    // void detachesOnPistonMove(BlockSource&, BlockPos const&) const;
    // void getExplosionResistance(Actor*) const;
    // void isValidAuxValue(int) const;
    // void onPlayerPlacing(BlockSource&, BlockPos const&, Actor&, unsigned char) const;
    // void isHurtableBlock() const;
    // void isAlphaTested() const;
    // void getParticleQuantityScalar() const;
     void onPlace(BlockSource&, BlockPos const&, Block const&) const;
    // void isObstructingChests(BlockSource&, BlockPos const&) const;
    // void getBlockState(HashedString const&) const;
    // void getLight() const;
    // void getShadeBrightness() const;
    // void isSeasonTinted(BlockSource&, BlockPos const&) const;
    // void neighborChanged(BlockSource&, BlockPos const&, BlockPos const&) const;
    // void getMobToSpawn(SpawnConditions const&, BlockSource&) const;
    // void getConnectedDirections(BlockPos const&, BlockSource&, bool&, bool&, bool&, bool&) const;
    // void forceExecuteTrigger(DefinitionTrigger const&, RenderParams&) const;
    // void executeEvent(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, RenderParams&) const;
    // void getAABB(BlockSource&, BlockPos const&, AABB&, bool) const;
    // void calcVariant(BlockSource&, BlockPos const&) const;
    // void isThinFenceBlock() const;
    // void getDefaultState() const;
    // void handleEntityInside(BlockSource&, BlockPos const&, Actor*, Vec3&) const;
    // void checkIsPathable(Actor&, BlockPos const&, BlockPos const&) const;
    // void getDestroySpeed() const;
    // void spawnResources(BlockSource&, BlockPos const&, std::__ndk1::vector<Item const*, std::__ndk1::allocator<Item const*> >*, float, int, bool) const;
    // void canHurtAndBreakItem() const;
    // void isRailBlock() const;
    // void liquidCanFlowIntoFromDirection(unsigned char, std::__ndk1::function<Block const& (BlockPos const&)> const&, BlockPos const&) const;
    // void getVisualShape(AABB&, bool) const;
    // void isWaterBlocking() const;
    // void onProjectileHit(BlockSource&, BlockPos const&, Actor const&) const;
    // void getPlacementBlock(Actor&, BlockPos const&, unsigned char, Vec3 const&, int) const;
    // void getIgnoresDestroyPermissions(Actor&, BlockPos const&) const;
    // void isDoorBlock() const;
    // void isSolid() const;
    // void canBeBrokenFromFalling() const;
    // void isInteraction() const;
    // void onRemove(BlockSource&, BlockPos const&) const;
    // void calcGroundFriction(Mob&, BlockPos const&) const;
    // void getBlendedCanRenderAsOpaque() const;
    // void initEntity(EntityRegistryOwned&);
    // void getColor(BlockSource&, BlockPos const&) const;
    // void clip(BlockSource&, BlockPos const&, Vec3 const&, Vec3 const&, bool, AABB const&) const;
    // void initParams(RenderParams&, BlockSource&, BlockPos const&, Actor*) const;
    // void breaksFallingBlocks() const;
    // void getFlameOdds() const;
    // void isAttachedTo(BlockSource&, BlockPos const&, BlockPos&) const;
    // void mayPick() const;
    // void addAABBs(BlockSource&, BlockPos const&, AABB const*, std::__ndk1::vector<AABB, std::__ndk1::allocator<AABB> >&) const;
    // void addCollisionShapes(BlockSource&, BlockPos const&, AABB const*, std::__ndk1::vector<AABB, std::__ndk1::allocator<AABB> >&, Actor*) const;
    // void isSolidBlockingBlockAndNotSignalSource() const;
    // void isInteractiveBlock() const;
    // void mayPick(BlockSource&, bool) const;
    // void playerWillDestroy(Player&, BlockPos const&) const;
    // void getLightEmission() const;
    // void toDebugString() const;
    // void randomlyModifyPosition(BlockPos const&, int&) const;
    // void onRedstoneUpdate(BlockSource&, BlockPos const&, int, bool) const;
    // void spawnResources(BlockSource&, BlockPos const&, Block const&, std::__ndk1::vector<Item const*, std::__ndk1::allocator<Item const*> >*, float, int, bool) const;
    // void getTranslucency() const;
    // void randomTick(BlockSource&, BlockPos const&, Random&) const;
    // void onStructureBlockPlace(BlockSource&, BlockPos const&) const;
    // void attack(Player*, BlockPos const&) const;
    // void getFlexibility(BlockSource&, BlockPos const&) const;
    // void playerDestroy(Player&, BlockPos const&) const;
    // void clip(BlockSource&, BlockPos const&, Vec3 const&, Vec3 const&, bool) const;
    // void hasBlockEntity() const;
    // void canBeBuiltOver(BlockSource&, BlockPos const&) const;
    // void isHeavy() const;
    // void onFallOn(BlockSource&, BlockPos const&, Actor&, float) const;
    // void popResource(BlockSource&, BlockPos const&, ItemInstance const&) const;
    // void getVariant() const;
    // void entityInside(BlockSource&, BlockPos const&, Actor&) const;
    // void isWallBlock() const;
    // void mayPlaceOn(BlockSource&, BlockPos const&) const;
    // void onFillBlock(BlockSource&, BlockPos const&, Block const&) const;
    // void getMappedFace(unsigned char) const;
    // void movedByPiston(BlockSource&, BlockPos const&) const;
    // void canContainLiquid() const;
    // void randomlyModifyPosition(BlockPos const&) const;
    // void getMapColor(BlockSource&, BlockPos const&) const;
    // void shouldRandomTickExtraLayer() const;
    // void onStructureNeighborBlockPlace(BlockSource&, BlockPos const&) const;
    // void getAllowsRunes() const;
    // void keepState(ItemState const&) const;
    // void getRedstoneProperty(BlockSource&, BlockPos const&) const;
    // void shouldStopFalling(Actor&) const;
    // void getSecondPart(BlockSource&, BlockPos const&, BlockPos&) const;
    // void onExploded(BlockSource&, BlockPos const&, Actor*) const;
    // void getRuntimeId() const;
    // void getThickness() const;
    // void pushesOutItems() const;
    // void initFromDefinition(BlockComponentGroupDescription const&);
    // void destroy(BlockSource&, BlockPos const&, Actor*) const;
    // void getColorForParticle(BlockSource&, BlockPos const&, Block const&) const;
    // void setFlammable(int, int) const;
    // void getColor() const;
    // void isStrippable(Block const&) const;
    // void mayConsumeFertilizer(BlockSource&) const;
    // void getSerializationId() const;
    // void buildDescriptionId() const;
    // void renderTwoFaced() const;
    // void getColorAtPos(BlockSource&, BlockPos const&) const;
    // void canFillAtPos(BlockSource&, BlockPos const&) const;
    // void getPlacementFacingAllExceptAxisY(Actor&, BlockPos const&, float);
    // void executeEvent(BlockSource&, BlockPos const&, Block const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, Actor&) const;
    // void updateEntityAfterFallOn(BlockPos const&, IActorMovementProxy&) const;
    // void mayPlace(BlockSource&, BlockPos const&, unsigned char) const;
    // void isEmpty() const;
    // void canHaveExtraData() const;
    // void canConnect(Block const&, unsigned char, Block const&) const;
    // void isStemBlock() const;
    // void canBeOriginalSurface() const;
    // void getStateMask(ItemState const&) const;
    // void asItemInstance(BlockSource&, BlockPos const&) const;
    // void getPlacementFacingAll(Actor&, BlockPos const&, float);
    // void addTag(HashedString const&);
    // void getDebugText(std::__ndk1::vector<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::allocator<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > > >&, BlockPos const&) const;
    // void hasProperty(BlockProperty) const;
    // void spawnBurnResources(BlockSource&, float, float, float) const;
    // void canSurvive(BlockSource&, BlockPos const&) const;
    // void getFriction() const;
    // void getBrightnessGamma() const;
    // void isStandingSign() const;
    // void hasVariableLighting() const;
    // void getBlockEntityType() const;
    // void mayPlace(BlockSource&, BlockPos const&) const;
    // void operator!=(Block const&) const;
    // void executeEvent(DefinitionTrigger&, RenderParams&) const;
    // void getStateFromLegacyData(unsigned short) const;
    // void getIconYOffset() const;
    // void pushesUpFallingBlocks() const;
    // void getMapColor() const;
    // void getResourceCount(Random&, int) const;
    // void getBlockStateGroup() const;
    // void copyState(Block const&, ItemState const&) const;
public:
    //Objects
    static Block * SIZE_OFFSET;
    static Block * BLOCK_DESCRIPTION_PREFIX;
};//Block

#endif // _BLOCK_H