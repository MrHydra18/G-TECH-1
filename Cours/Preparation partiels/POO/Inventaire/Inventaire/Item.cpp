#include "Item.h"

std::vector<Item> Item::Inventory;

void Item::AddItem(std::string name, int value)
{
	Inventory.push_back(Item(name, value));
}

void Item::DisplayInventory()
{
	for (const auto& c : Inventory)
	{
		std::cout << c.name << " a une valeur de " << c.value << " pieces d'or." << std::endl;
	}
}