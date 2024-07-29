//
// Created by 30225 on 2023/7/24.
//

#ifndef MCENGINE_ITEMFACTORY_HPP
#define MCENGINE_ITEMFACTORY_HPP

#include <map>
#include <vector>
#include <jni.h>
#include "../../headers/mojang/CreativeItemCategory.h"
#include "../../headers/feifan/ItemFaker.hpp"
#include "headers/feifan/Other.hpp"
#include "IDPool.hpp"

class ItemFactory
{
private:
    std::string name;
    std::string iconName;
    int iconData;
    CreativeItemCategory type;
    Item *ptr;
public:
    static std::vector<ItemFactory*> normalItemsPoolArray;
    ItemFactory(std::string name, std::string iconName, int iconData, const CreativeItemCategory type) {
        this -> name = name;
        this -> iconName = iconName;
        this -> iconData = iconData;
        this -> type = type;
        this -> ptr = nullptr;
    }
    static ItemFactory* createObj(const char *name, const char *iconName,int iconData, const CreativeItemCategory type) {
        auto* item = new ItemFactory(name, iconName, iconData, type);
        normalItemsPoolArray.emplace_back(item);
        IDPool::setMap(name);
        return item;
    }
    void setItemPtr(Item *ptr_) {
        ptr = ptr_;
    }
    std::string getName() {
        return name;
    };
    std::string getIconName() {
        return iconName;
    };
    int getIconData()  {
        return iconData;
    };
    CreativeItemCategory getType() {
        return type;
    };
    Item *getPtr() {
        return ptr;
    };
};

#endif //MCENGINE_ITEMFACTORY_HPP
