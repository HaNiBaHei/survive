#ifndef ITEM_H
#define ITEM_H

enum ItemTypes {IT_DEFAULT = 0, IT_RANGEWEAPON, IT_MELEEWEAPON};

class Item
{
private:
	void initVariables();

protected:
	// Variables //
	short unsigned type;
	unsigned level;
	unsigned value;

public:
	Item(unsigned level, unsigned value);
	virtual ~Item();

	// Functions //
	virtual Item* clone() = 0;

};

#endif