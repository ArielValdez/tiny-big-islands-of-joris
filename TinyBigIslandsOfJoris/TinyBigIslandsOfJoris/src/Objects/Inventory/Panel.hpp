#pragma once
#include "Item.hpp"

class Panel {
public:
	// Cannot drop or sort item when this is true
	bool IsFavorite = false;
	bool Focused = false;
	Item* CurrentItem;

public:
	Panel() {
		CurrentItem = nullptr;
	}

	void UseItem();

	~Panel();
private:
};