#include "stdafx.h"
#include "RangeWeapon.h"

RangeWeapon::RangeWeapon(unsigned value)
	:Item(value)
{
	this->type = ItemTypes::IT_RANGEWEAPON;
}

RangeWeapon::~RangeWeapon()
{

}
