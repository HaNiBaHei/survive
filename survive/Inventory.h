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
	void nullify(const unsigned from = 0);
	void freeMemory();

public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	// Accessors //
	const unsigned& size() const;
	const unsigned& maxSize() const;


	// Modifiers //


	// Functions //
	void clear();
	const bool emtpy() const;

	const bool add(Item* item);
	const bool remove(const unsigned index);

	const bool saveToFile(const std::string fileName);
	const bool loadFromFile(const std::string fileName);

};

#endif // !INVENTORY_H
