#pragma once
#include "../Objects/Enums/ItemType.hpp"

class Item {
public:

public:
	Item() = default;
	Item(ItemType type, size_t maxQuantity);

	~Item() {

	}
private:
	ItemType Type;
	size_t MaxQuantity;
	size_t Quantity;
	bool Stackable; // Depends on MaxQuantity
	char* Description;
};