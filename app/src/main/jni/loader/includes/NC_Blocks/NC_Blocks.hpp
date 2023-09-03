//
// Created by 30225 on 2023/8/25.
//

#ifndef MCENGINE_NC_BLOCKS_HPP
#define MCENGINE_NC_BLOCKS_HPP
//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改//勿改

#include "../../headers/CreativeItemCategory.h"
#include <vector>
class NC_Blocks
{
private:
    const char* name;
    int material;
    const CreativeItemCategory category;
    float hardness = 1.5;//原版硬度是destroyTime，突出一个屎山不改
    float blastResistance = 10;//原版抗爆是explodeable。。。。。。。
public:
    NC_Blocks(const char*,int,const CreativeItemCategory,float,float);
    NC_Blocks(const char*,int,const CreativeItemCategory);
    static NC_Blocks* createObj(const char *name,const CreativeItemCategory type);
    static NC_Blocks* createObj(const char *name,const CreativeItemCategory type,float);
};
extern std::vector<NC_Blocks *> blocksPoolArray;
//最终值=(5/3)*抗性

#endif //MCENGINE_NC_BLOCKS_HPP
