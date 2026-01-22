#include "Archer.h"

void Archer::heal(int amount)
{
	health = health + amount;

	if (health >= maxHealth)
		health = maxHealth;
}

void Archer::DisplayStats()
{
	std::cout << name << " a " << health << " PV." << std::endl;
}
