#pragma once
#include "Entity.h"
#include "Alive.h"

class BreakableObject : public Entity, public Alive
{
public:

	BreakableObject(Vector2D pos, float maxHealth, float Health) : Entity(pos), Alive(maxHp, Hp) { 
		std::cout << "Breakable Object just created at x = " << GetPos().x << " and y = " << GetPos().y << " with "<< maxHealth << " HP" << std::endl; };

	void TakeDamage(float dmg) override;
};

