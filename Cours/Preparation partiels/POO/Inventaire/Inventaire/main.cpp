#include "Character.h"
#include "Archer.h"
#include "Warrior.h"
#include "Item.h"

int main()
{
	Warrior Warrior(10, 10, "Manolo");
	Archer Archer(5, 7, "Patricio");


	Item::AddItem("Epee   en bois", 3);
	Item::AddItem("Potion de soin", 5);

	Warrior.DisplayStats();
	Archer.DisplayStats();
	Archer.heal(8);
	Item::DisplayInventory();
	Archer.DisplayStats();

	return 0;
}