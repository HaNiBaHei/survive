#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned value)
    :RangeWeapon(value)
{
}

Bow::~Bow()
{

}

Bow* Bow::clone()
{
    return new Bow(*this);
}
