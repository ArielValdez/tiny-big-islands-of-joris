#include "Inventory.hpp"

Inventory::Inventory() {
	Size = 50;
	TooltipSize = 10;
	Panels = new Panel[Size];
}

Inventory::Inventory(size_t sizeInventory) {
	Size = sizeInventory;
	TooltipSize = 10;
	Panels = new Panel[Size];
}

void Inventory::GetFocusedChannel(int idx) {
	int currentIdx = CurrentTooltipIdx + idx;
	if (currentIdx < 0)
	{
		currentIdx = TooltipSize - 1;
	}
	else if (currentIdx >= TooltipSize)
	{
		currentIdx = 0;
	}

	Panels[CurrentTooltipIdx].Focused = false;
	CurrentTooltipIdx = currentIdx;
	Panels[CurrentTooltipIdx].Focused = true;

	CurrentPanel = Panels[CurrentTooltipIdx];
}

void Inventory::AddItem(Item* item) {
	for (size_t panelIdx = 0; panelIdx < Size; ++panelIdx) {
		Panel p = Panels[panelIdx];
		if (p.CurrentItem == NULL)
		{
			p.CurrentItem = item;
		}
	}
}

Item* Inventory::DropItem(Panel* panel) {
	// Remove item from inventory then move it to world
	Item* item = panel->CurrentItem;
	panel->CurrentItem = nullptr;

	return item;
}

Item* Inventory::DropItem(Panel* panel, size_t qty) {
	// Remove x qty of item from inventory then move it to world
	return nullptr;
}

Item* Inventory::DropItem(size_t panelIdx) {
	Panel* panel = &Panels[panelIdx];
	Item* item = panel->CurrentItem;
	panel->CurrentItem = nullptr;

	return item;

}

Item* Inventory::DropItem(size_t panelIdx, size_t qty) {
	return nullptr;
}

void Inventory::DestroyItem(Item* item) {
	item = nullptr;
}

void Inventory::SortInventory() {

}

Inventory::~Inventory() {
	delete[] Panels;
	Panels = nullptr;
}