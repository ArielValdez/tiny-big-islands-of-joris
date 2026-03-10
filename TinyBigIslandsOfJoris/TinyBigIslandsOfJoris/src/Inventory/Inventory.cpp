#include "Inventory.hpp"

Inventory::Inventory() {
	Size = 50;
	Items[Size] = {  };
}

Inventory::Inventory(size_t sizeInventory) {
	Size = sizeInventory;
	Items[Size] = {  };
}

Inventory::~Inventory() {
	delete[] Items;
	Items = nullptr;
}