#ifndef INVENTORY_H
#define INVENTORY_H

#include"Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned nrOfItem;
	unsigned capacity;

	// Private Functions //
	void initialize();
	void expand();
	void nullify(const unsigned from = 0);
	void freeMemory();

public:
	Inventory();
	virtual ~Inventory();

	// Functions //

};

#endif // !INVENTORY_H
