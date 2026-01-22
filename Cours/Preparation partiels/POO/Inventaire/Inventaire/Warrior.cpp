#include "Warrior.h"

void Warrior::heal(int amount)
{
	health = health + amount;

	if (health >= maxHealth)
		health = maxHealth;
}

void Warrior::DisplayStats()
{
	std::cout << name << " a " << health << " PV." << std::endl;
}
