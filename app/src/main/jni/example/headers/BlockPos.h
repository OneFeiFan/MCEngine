#ifndef EX_BLOCK_POS_H  
#define EX_BLOCK_POS_H
class BlockPos {
    public:
    int x, y, z;
    BlockPos(int x,int y,int z) : x(x), y(y), z(z) {};
    ~BlockPos(){
        
    };
};
#endif