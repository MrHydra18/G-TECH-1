#include "BreakableObject.h"

void BreakableObject::TakeDamage(float dmg)
{ 
	Hp -= dmg; 
	if (Hp <= 0) 
		std::cout << "Breakable Object just broke" << std::endl;
}
