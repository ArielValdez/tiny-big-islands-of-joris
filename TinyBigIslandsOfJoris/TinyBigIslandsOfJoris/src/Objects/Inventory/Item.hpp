#pragma once
#include "../EntityComponentSystem.hpp"
#include "../Enums/ItemType.hpp"

class Item : public Entity {
public:

public:
	Item(Manager& manager);
	Item(Manager& manager, ItemType type, size_t maxQuantity, const char* desc);

	virtual void Use() {
		std::cout << "Using item" << std::endl;
	}

	~Item() {

	}
private:
	ItemType Type;
	size_t MaxQuantity;
	size_t Quantity;
	bool IsStackable; // Depends on MaxQuantity
	const char* Description;
};