#include "Bullet.h"

void Bullet::OnCollision(Entity* other)
{
	if (other->IsTag(0))
		Destroy();
	else
		return;
}

void Bullet::OnInitialize()
{
	SetTag(2);
}
