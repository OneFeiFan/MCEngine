#ifndef EX_ACTOR_H
#define EX_ACTOR_H
class Actor
{
public:
    virtual int getDimensionId() const;
    int getRegion() const;//_ZNK5Actor9getRegionEv

public:
    bool isSneaking() const;
    int getDimension() const;
};
#endif