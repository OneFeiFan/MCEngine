#ifndef EX_FAKE_BLOCKLEGACY_HPP
#define EX_FAKE_BLOCKLEGACY_HPP
#include <dlfcn.h>
class BlockLegacy
{
public:
    char *getRawNameId() const;
    int getBlockItemId() const;
}; //
// fake区域
static int (*fake_BlockLegacy_getBlockItemId)(BlockLegacy *);
#endif