#include "Zombi.h"


void Zombie::OnCollision(Entity* other)
{
	if (other->IsTag(1) || other->IsTag(2))
		Destroy();
	else
		return;
}


void Zombie::OnInitialize()
{
	SetTag(0);
}