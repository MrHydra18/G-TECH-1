#include "Plant.h"


void Plant::OnCollision(Entity* other)
{
	std::cout << "Plant has collide\n";
}

void Plant::OnInitialize()
{
	SetTag(1);
}
