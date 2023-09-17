#ifndef EX_FAKE_BLOCKLEGACY_HPP
#define EX_FAKE_BLOCKLEGACY_HPP

#include <string>
#include "sharedptr.h"
#include "CreativeItemCategory.h"

class BlockLegacy
{
public:
    char *getRawNameId() const;

    int getBlockItemId() const;
}; //
// fake区域
extern short (*fake_BlockLegacy_getBlockItemId)(BlockLegacy *);

extern WeakPtr<BlockLegacy> (*fake_BlockLegacy_createWeakPtr)(BlockLegacy *);

extern BlockLegacy *(*fake_BlockLegacy_setCategory)(BlockLegacy *, CreativeItemCategory);

extern BlockLegacy *(*fake_BlockLegacy_setDestroyTime)(BlockLegacy *, float);

extern BlockLegacy *(*fake_BlockLegacy_setExplodeable)(BlockLegacy *, float);

extern std::string (*fake_BlockLegacy_getCommandName)(BlockLegacy *);

extern char *(*fake_BlockLegacy_getRawName)(BlockLegacy *);

//_ZNK11BlockLegacy12getRawNameIdEv
//hook区
extern BlockLegacy *(*base_BlockLegacy_setExplodeable)(BlockLegacy *, float);
extern BlockLegacy *NC_BlockLegacy_setExplodeable(BlockLegacy *, float);
#endif