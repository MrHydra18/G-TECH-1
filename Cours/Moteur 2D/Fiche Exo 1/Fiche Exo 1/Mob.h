#pragma once
#include"Entity.h"
#include"Alive.h"
#include"AMovable.h"


class Mob : public Entity, public Alive, public AMovable
{
public:

	Mob(Vector2D pos, float maxHealth, float Health, Vector2D dir) : Entity(pos), Alive(maxHealth, Health), AMovable(dir) {
		std::cout << "Mob just created at x = " << GetPos().x << " and y = " << GetPos().y << " with " << GetHp() << " HP, with direction x = " << GetDirection().x << " and y = " << GetDirection().y << std::endl;
	}

	void TakeDamage(float dmg) override;
	void Move() override;
};

