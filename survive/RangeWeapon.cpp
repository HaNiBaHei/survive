#include "stdafx.h"
#include "RangeWeapon.h"

RangeWeapon::RangeWeapon(unsigned level, unsigned value, std::string texture_file)
	:Weapon(level, value, texture_file)
{
	this->type = ItemTypes::IT_RANGEWEAPON;
}

RangeWeapon::~RangeWeapon()
{

}

void RangeWeapon::generate(const unsigned levelMin, const unsigned levelMax)
{

}
