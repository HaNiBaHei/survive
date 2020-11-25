#ifndef RANGEWEAPON_H
#define RANGEWEAPON_H

#include "Item.h"

class Item;

class RangeWeapon :
    public Item
{
private:


public:
    RangeWeapon(unsigned value);
    virtual ~RangeWeapon();

    // Functions //
    virtual RangeWeapon* clone() = 0;
};

#endif