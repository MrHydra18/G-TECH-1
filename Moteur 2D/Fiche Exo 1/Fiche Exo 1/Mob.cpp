#include "Mob.h"

void Mob::TakeDamage(float dmg)
{
	Hp -= dmg;
	if (Hp <= 0)
		std::cout << "Player just died" << std::endl;
}

void Mob::Move()
{
	SetPos(Vector2D(GetPos().x + GetDirection().x * GetSpeed(), GetPos().y + GetDirection().y * GetSpeed()));
	std::cout << "Mob move to x = " << GetPos().x << " and y = " << GetPos().y << std::endl;

}
