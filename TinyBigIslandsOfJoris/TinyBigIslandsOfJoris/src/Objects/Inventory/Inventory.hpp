#pragma once
#include "Item.hpp"
#include "Panel.hpp"
#include "../EntityComponentSystem.hpp"

class Inventory {
public:
	size_t CurrentTooltipIdx;
	Panel CurrentPanel;

public:
	Inventory();
	Inventory(size_t sizeInventory);

	void AddItem(Item* item);
	Item* DropItem(Panel* panel);
	Item* DropItem(Panel* panel, size_t qty);
	Item* DropItem(size_t panelIdx);
	Item* DropItem(size_t panelIdx, size_t qty);
	void GetFocusedChannel(int idx);

	void DestroyItem(Item* item); // Trashcan On Inventory
	void SortInventory();

	~Inventory();

private:
	size_t Size;
	size_t TooltipSize;
	Panel* Panels;
	Panel* ToolTip;
};
