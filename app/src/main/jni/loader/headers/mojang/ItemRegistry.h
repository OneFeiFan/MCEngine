//
// Created by 25843 on 2024/7/21.
//

#ifndef MCENGINE_ITEMREGISTRY_H
#define MCENGINE_ITEMREGISTRY_H

#include <string>
#include "Item.h"
#include "sharedptr.h"

class ItemRegistry
{
public:
    // Fields
    // char filler_ItemRegistry[UNKNOW_SIZE];
public:
    // Methods
    //  void getItem(Block const&);
    //  void getItemResponseFactory();
    //  void setItemId(HashedString const&, short, bool);
    //  void lookupByNameNoAlias(HashedString const&);
    //  void _loadItemDefinition(Json::Value&, bool, std::__ndk1::function<void (WeakPtr<Item>&, Json::Value&)>, bool, ItemType, PackType);
    //  void clearItemAndCreativeItemRegistry();
    //  void getNameToItemMap();
    //  void registerItem(SharedPtr<Item>);
    //  void remapToLegacyNameByHash(unsigned long long);
    //  void alterAvailableCreativeItems(ActorInfoRegistry*, LevelData&);
    //  void initServerData(ResourcePackManager&, Experiments const&, ItemType);
    //  void initClientData(ResourcePackManager&, Experiments const&);
    //  void lookupByNameNoAlias(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    //  void setOwningThreadId(std::__ndk1::__thread_id);
    //  void isCreativeItem(ItemInstance const&);
    //  void registerAlias(HashedString const&, HashedString const&, BaseGameVersion const&);
    //  void digestServerItemComponents(std::__ndk1::vector<std::__ndk1::pair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, CompoundTag>, std::__ndk1::allocator<std::__ndk1::pair<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, CompoundTag> > > const&);
    //  void lookupByName(int&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    //  void lookupByName(HashedString const&);
    //  void shutdown();
    //  void registerComplexAlias(HashedString const&, std::__ndk1::function<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > (short)>);
    //  void getItem(HashedString const&);
    //  void getLegacyIDFromName(HashedString const&);
    //  void getItem(BlockLegacy const&);
    //  void registerLegacyID(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, short);
    //  void getNameFromAlias(HashedString const&, int);
    //  void matchServerItemIds(std::__ndk1::vector<ItemData, std::__ndk1::allocator<ItemData> > const&);
    //  void getNameFromLegacyID(short);
    //  void getItemCount();
    //  void unregisterItem(HashedString const&);
    //  void lookupByName(int&, int&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&);
    //  void finishedRegistration();
    //  void startRegistration();
    //  void initCreativeItemsClient(BaseGameVersion const&, std::__ndk1::vector<CreativeItemEntry, std::__ndk1::allocator<CreativeItemEntry> >&&);
    //  void _parseItemDefinition(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, bool, std::__ndk1::function<void (WeakPtr<Item>&, Json::Value&)>, bool, ItemType, PackType);
    //  void generateServerItemComponentTags();
    //  void _isOwningThread();
    //  void registerLegacyMapping(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&, BaseGameVersion const&);
    //  void initCreativeItemsServer(ActorInfoRegistry*, BlockDefinitionGroup*, bool, BaseGameVersion const&, Experiments const&, std::__ndk1::function<void (ActorInfoRegistry*, BlockDefinitionGroup*, CreativeItemRegistry*, bool, BaseGameVersion const&, Experiments const&)>);
    static SharedPtr<Item> getItem(short);

    int getMaxItemID();

    // WeakPtr<Item> ItemRegistry::registerItemShared<Item, short&>(std::string const& name, short& id);
    template<typename ItemType, typename... Args>
    static WeakPtr<ItemType> registerItemShared(const std::string &itemName, Args &&...args);

public:
    // Objects
    static ItemRegistry *mResponseFactory;
    static ItemRegistry *mCompatibilityCheckLock;
    static ItemRegistry *mCheckForItemWorldCompatibility;
    static ItemRegistry *mNameToItemMap;
    static ItemRegistry *mDeadItemRegistry;
    static ItemRegistry *MINECRAFT_NAMESPACE;
    static ItemRegistry *mOwnerThread;
    static ItemRegistry *mReverseAliasLookupMap;
    static ItemRegistry *mWorldBaseGameVersion;
    static ItemRegistry *mItemRegistry;
    static ItemRegistry *mIdToItemMap;
    static ItemRegistry *mLegacyIDToNameMap;
    static ItemRegistry *mComplexAliasLookupMap;
    static ItemRegistry *mItemAliasLookupMap;
    static ItemRegistry *mServerInitializingCreativeItems;
};

#endif //MCENGINE_ITEMREGISTRY_H
