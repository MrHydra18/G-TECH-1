#include "Player.h"

void Player::TakeDamage(float dmg)
{
	Hp -= dmg;
	if (Hp <= 0)
		std::cout << "Mob just died" << std::endl;
}

void Player::Move()
{
	SetPos(Vector2D(GetPos().x + GetDirection().x * GetSpeed(),
		GetPos().y + GetDirection().y * GetSpeed()));
	std::cout << "Mob move to x = " << GetPos().x << " and y = " << GetPos().y << std::endl;
}

void Player::Attack(Alive* other)
{
	other->TakeDamage(damage);
	std::cout << "Player just attacked \n";
}