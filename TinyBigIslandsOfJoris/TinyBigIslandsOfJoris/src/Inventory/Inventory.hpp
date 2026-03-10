#pragma once
#include "Item.hpp"

class Inventory {
public:

public:
	Inventory();
	Inventory(size_t sizeInventory);

	~Inventory();

private:
	size_t Size;
	Item* Items;
};
