#include "Panel.hpp"

void Panel::UseItem() {
	if (CurrentItem != nullptr)
	{
		CurrentItem->Use();
	}
	else
	{
		std::cout << "No item in hand..." << std::endl;
	}
}

Panel::~Panel() {

}