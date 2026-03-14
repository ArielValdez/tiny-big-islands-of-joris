#include "Item.hpp"

Item::Item(Manager& manager) : Entity(manager) {
	Type = NONE;
	MaxQuantity = 1;
	Quantity = 1;
	IsStackable = false;
	Description = "<Verb> this";
}

Item::Item(Manager& manager,ItemType type, size_t maxQuantity, const char* desc) : Entity(manager) {
	Type = type;
	MaxQuantity = maxQuantity;
	Quantity = 1;
	IsStackable = (MaxQuantity > 1);
	Description = desc;
}