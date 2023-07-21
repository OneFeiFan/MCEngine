#include <dlfcn.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include "includes/CydiaSubstrate.h"
#include "includes/EXHookFR.hpp"
#include "headers/BlockPos.h"
#include "headers/BlockSource.h"
#include "headers/ItemStack.h"
#include "headers/sharedptr.h"
#include "headers/ItemInstance.h"
#include "headers/CreativeItemCategory.h"
#include "AllHeaders.h"


#include "Jni2Native.hpp"
class IconData
{
private:
    const char *name = " ";
    int data = 0;

public:
    IconData(const char *name, int data);
    const char *getName();
    int getData();
};
IconData::IconData(const char *name, int data) : name(name), data(data) {}
const char *IconData::getName()
{
    return this->name;
}
int IconData::getData()
{
    return this->data;
}
class EX_Item
{
private:
    const char *name;
    const char *iconName;
    const int iconData;
    const bool inCreative;
    const CreativeItemCategory type = CreativeItemCategory::Construction;
    Item *ptr;

public:
    EX_Item(const char *name, const char *iconName, const int iconData, const bool inCreative);
    EX_Item(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type);
    void setItemPtr(Item *ptr);
    const char *getName() const;
    const char *getIconName() const;
    int getIconData() const;
    bool isInCreative() const;
    CreativeItemCategory getType();
    Item *getPtr();
};
EX_Item::EX_Item(const char *name, const char *iconName, const int iconData, const bool inCreative) : name(name), iconName(iconName), iconData(iconData), inCreative(inCreative)
{
    this->ptr = nullptr;
};
EX_Item::EX_Item(const char *name, const char *iconName, const int iconData, const bool inCreative, const CreativeItemCategory type) : name(name), iconName(iconName), iconData(iconData), inCreative(inCreative), type(type)
{
    this->ptr = nullptr;
};
void EX_Item::setItemPtr(Item *ptr)
{
    this->ptr = ptr;
}
const char *EX_Item::getName() const
{
    return this->name;
}
const char *EX_Item::getIconName() const
{
    return this->iconName;
}
int EX_Item::getIconData() const
{
    return this->iconData;
}
bool EX_Item::isInCreative() const
{
    return this->inCreative;
}
Item *EX_Item::getPtr()
{
    return this->ptr;
}
CreativeItemCategory EX_Item::getType()
{
    return this->type;
}

EX_Item *itemObj = new EX_Item("test", "apple", 0, 1);
EX_Item *itemObj1 = new EX_Item("test1", "apple_golden", 0, 1, CreativeItemCategory::Items);
std::vector<EX_Item *> itemsPoolArray{itemObj, itemObj1};
std::map<short, EX_Item *> itemsPoolMap;

void (*base_Block_onPlace)(void *, BlockSource &, BlockPos const &, Block const &);
void EX_Block_onPlace(void *ptr, BlockSource &blockSource, BlockPos const &pos, Block const &block)
{
    // jclass CLASS = EXHookFR::hookerPtr->Class;
    // invokeCallback(CLASS, "onBlockPlace", "(JJ)V", (jlong)&blockSource, (jlong)&pos);
    return base_Block_onPlace(ptr, blockSource, pos, block);
}
void (*base_Item_useOn)(void *, ItemStack &, Actor &, int, int, int, unsigned char, float, float, float);
void EX_Item_useOn(void *ptr, ItemStack &itemstack, Actor &actor, int x, int y, int z, unsigned char d, float e, float f, float g)
{
    return base_Item_useOn(ptr, itemstack, actor, x, y, z, d, e, f, g);
}
WeakPtr<Item> (*base_registerItem)(std::string const &, short);
WeakPtr<Item> EX_registerItem(std::string const &str, short num)
{

    return base_registerItem(str, num);
}

void (*base_Item_setCategory)(Item *, int);
void EX_Item_setCategory(uint32_t ptr, int num)
{
}
// Item test;
class Experiments;
uint32_t (*base_VanillaItems_registerItems)(void *, Experiments const &, bool);
uint32_t EX_VanillaItems_registerItems(void *ptr, Experiments const &e, bool b)
{
    uint32_t obj = base_VanillaItems_registerItems(ptr, e, b);
    printf("base_VanillaItems_registerItems\n");
    Item *temp = nullptr;
    for (int i = 0; i < itemsPoolArray.size(); ++i)
    {
        temp = fake_ItemRegistry_registerItemShared(itemsPoolArray[i]->getName(), (short &)(++fake_ItemRegistry_mMaxItemID)).get();
        itemsPoolArray[i]->setItemPtr(temp);
        itemsPoolMap.insert(std::pair<short &, EX_Item *>((short &)fake_ItemRegistry_mMaxItemID, itemsPoolArray[i]));
    }
    return obj;
}
void (*base_Item_setIcon)(void *, std::string const &, short);
void EX_Item_setIcon(void *ptr, std::string const &str, short data)
{
    return base_Item_setIcon(ptr, str, data);
}

void (*base_Item_setIcon1)(void *, TextureUVCoordinateSet const &);
void EX_Item_setIcon1(void *ptr, TextureUVCoordinateSet const &a)
{
    return base_Item_setIcon1(ptr, a);
}

bool aa = 1;
bool bb = 1;
TextureUVCoordinateSet test;
void (*base_Item_getTextureUVCoordinateSet)(void *, std::string, int);
void EX_Item_getTextureUVCoordinateSet(void *ptr, std::string str, int a)
{
    return base_Item_getTextureUVCoordinateSet(ptr, str, a);
}
TextureUVCoordinateSet const &(*base_Item_getIcon)(Item *, ItemStackBase const &, int, bool);
TextureUVCoordinateSet const &EX_Item_getIcon(Item *ptr, ItemStackBase const &a, int b, bool c)
{
    return base_Item_getIcon(ptr, a, b, c);
}
//
void (*test11)(std::string, std::string, int);
void test_(std::string str1, std::string str2, int i)
{
    return test11(str1, str2, i);
}
uint32_t (*base_VanillaItems_initClientData)(void *, Experiments const &);
uint32_t EX_VanillaItems_initClientData(void *ptr, Experiments const &e)
{
    uint32_t obj = base_VanillaItems_initClientData(ptr, e);
    EX_Item *temp = nullptr;
    for (int i = 0; i < itemsPoolArray.size(); ++i)
    {
        temp = itemsPoolArray[i];
        base_Item_setIcon(temp->getPtr(), temp->getIconName(), temp->getIconData());
        base_Item_setCategory(temp->getPtr(), 4);
        std::cout << 111 << std::endl;
    }
    return obj;
}
void (*base_Item_addCreativeItem)(Item *, short);
void EX_Item_addCreativeItem(Item *obj, short a)
{
    short id = fake_Item_getId(obj);
    if (itemsPoolMap.count(id))
    {
        if (itemsPoolMap[id]->isInCreative())
        {
            base_Item_addCreativeItem(obj, 0);
        }
        return;
    }
    return base_Item_addCreativeItem(obj, a);
}
class ActorInfoRegistry;
class BlockDefinitionGroup;
class CreativeItemRegistry;
class BaseGameVersion;
uint32_t (*base_VanillaItems_serverInitCreativeItemsCallback)(void *, ActorInfoRegistry *, BlockDefinitionGroup *, CreativeItemRegistry *, bool, BaseGameVersion const &, Experiments const &);
uint32_t EX_VanillaItems_serverInitCreativeItemsCallback(void *ptr, ActorInfoRegistry *a, BlockDefinitionGroup *b, CreativeItemRegistry *c, bool d, BaseGameVersion const &e, Experiments const &f)
{
    uint32_t obj = base_VanillaItems_serverInitCreativeItemsCallback(ptr, a, b, c, d, e, f);
    EX_Item *temp = nullptr;
    for (int i = 0; i < itemsPoolArray.size(); ++i)
    {
        temp = itemsPoolArray[i];

        base_Item_setCategory(temp->getPtr(), 2);
        std::cout << 111 << std::endl;
    }
    return obj;
}
void (*base_ItemStackBase)(void *, Item const &, int, int);
void EX_ItemStackBase(void *ptr, Item const &obj, int a, int b)
{
    return base_ItemStackBase(ptr, obj, a, b);
}
class ResourceLocation
{
};
void (*base_TextureUVCoordinateSet_TextureUVCoordinateSet)(void *, float, float, float, float, unsigned short, unsigned short, ResourceLocation, float, unsigned short);
void EX_TextureUVCoordinateSet_TextureUVCoordinateSet(void *ptr, float a, float b, float c, float d, unsigned short e, unsigned short f, ResourceLocation g, float h, unsigned short i)
{
    base_TextureUVCoordinateSet_TextureUVCoordinateSet(ptr, a, b, c, d, e, f, g, h, i);
};
void EXHookFR::init()
{
    // fake区
    fake_Actor_getRegion = (int (*)(Actor *))dlsym(this->MCHandle, "_ZNK5Actor9getRegionEv");
    fake_Actor_isSneaking = (bool (*)(Actor *))dlsym(this->MCHandle, "_ZNK5Actor10isSneakingEv");
    fake_BlockLegacy_getBlockItemId = (int (*)(BlockLegacy *))dlsym(this->MCHandle, "_ZNK11BlockLegacy14getBlockItemIdEv");
    Fake_BlockSource_getBlock = (Block * (*)(BlockSource *, int, int, int)) dlsym(this->MCHandle, "_ZNK11BlockSource8getBlockEiii");
    fake_Item_getId = (short (*)(Item *))dlsym(this->MCHandle, "_ZNK4Item5getIdEv");
    fake_ItemRegistry_mMaxItemID = (ItemRegistry **)dlsym(this->MCHandle, "_ZN12ItemRegistry10mMaxItemIDE");
    fake_ItemRegistry_registerItemShared = (WeakPtr<Item>(*)(const std::string &, short &))dlsym(this->MCHandle, "_ZN12ItemRegistry18registerItemSharedI4ItemJRsEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEDpOT0_");
    fake_ItemStackBase_getId = (short (*)(ItemStackBase *))dlsym(this->MCHandle, "_ZNK13ItemStackBase5getIdEv");
    // hook区
    void *ptr = (void *)dlsym(this->MCHandle, "_ZNK5Block7onPlaceER11BlockSourceRK8BlockPosRKS_");
    MSHookFunction(ptr, (void *)&EX_Block_onPlace, (void **)&base_Block_onPlace);
    ptr = (void *)dlsym(this->MCHandle, "_ZNK4Item5useOnER9ItemStackR5Actoriiihfff");
    MSHookFunction(ptr, (void *)&EX_Item_useOn, (void **)&base_Item_useOn);
    ptr = (void *)dlsym(this->MCHandle, "_ZN12ItemRegistry12registerItemI4ItemJEEE7WeakPtrIT_ERKNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEsDpOT0_");
    MSHookFunction(ptr, (void *)&EX_registerItem, (void **)&base_registerItem);
    ptr = (void *)dlsym(this->MCHandle, "_ZN12VanillaItems13registerItemsERK11Experimentsb");
    MSHookFunction(ptr, (void *)&EX_VanillaItems_registerItems, (void **)&base_VanillaItems_registerItems);
    ptr = (void *)dlsym(this->MCHandle, "_ZN12VanillaItems14initClientDataER11Experiments");
    MSHookFunction(ptr, (void *)&EX_VanillaItems_initClientData, (void **)&base_VanillaItems_initClientData);
    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item7setIconERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    MSHookFunction(ptr, (void *)&EX_Item_setIcon, (void **)&base_Item_setIcon);
    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item7setIconERK22TextureUVCoordinateSet");
    MSHookFunction(ptr, (void *)&EX_Item_setIcon1, (void **)&base_Item_setIcon1);
    ptr = (void *)dlsym(this->MCHandle, "_ZNK4Item7getIconERK13ItemStackBaseib");
    MSHookFunction(ptr, (void *)&EX_Item_getIcon, (void **)&base_Item_getIcon);
    ptr = (void *)dlsym(this->MCHandle, "_ZN13ItemStackBaseC2ERK4Itemii");
    MSHookFunction(ptr, (void *)&EX_ItemStackBase, (void **)&base_ItemStackBase);
    ptr = (void *)dlsym(this->MCHandle, "_ZN12VanillaItems31serverInitCreativeItemsCallbackEP17ActorInfoRegistryP20BlockDefinitionGroupP20CreativeItemRegistrybRK15BaseGameVersionRK11Experiments");
    MSHookFunction(ptr, (void *)&EX_VanillaItems_serverInitCreativeItemsCallback, (void **)&base_VanillaItems_serverInitCreativeItemsCallback);
    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item15addCreativeItemEPS_s");
    MSHookFunction(ptr, (void *)&EX_Item_addCreativeItem, (void **)&base_Item_addCreativeItem);
    ptr = (void *)dlsym(this->MCHandle, "_ZN22TextureUVCoordinateSetC1Efffftt16ResourceLocationft");
    MSHookFunction(ptr, (void *)&EX_TextureUVCoordinateSet_TextureUVCoordinateSet, (void **)&base_TextureUVCoordinateSet_TextureUVCoordinateSet);
    ptr = (void *)dlsym(this->MCHandle, "_ZN4Item25getTextureUVCoordinateSetERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEi");
    MSHookFunction(ptr, (void *)&EX_Item_getTextureUVCoordinateSet, (void **)&base_Item_getTextureUVCoordinateSet);
    ptr = (void *)dlsym(this->MCHandle, "_Z15setIconIfLegacyRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEES7_i");
    MSHookFunction(ptr, (void *)&test_, (void **)&test11);
    base_Item_setCategory = (void (*)(Item *, int))dlsym(this->MCHandle, "_ZN4Item11setCategoryE20CreativeItemCategory");
}
