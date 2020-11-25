#ifndef BOW_H
#define BOW_H

#include "RangeWeapon.h"

class RangeWeapon;

class Bow :
    public RangeWeapon
{
private:

public:
    Bow(unsigned value);
    virtual ~Bow();

    virtual Bow* clone();
};

#endif