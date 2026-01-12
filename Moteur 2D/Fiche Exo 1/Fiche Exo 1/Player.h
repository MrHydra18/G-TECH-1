#pragma once
#include"Entity.h"
#include"Alive.h"
#include"AMovable.h"
#include"IAttacker.h"

class Player : public Entity, public Alive, public AMovable, public IAttacker
{
private:

	float damage = 10;

public:

	Player(Vector2D pos, float maxHp, float Hp, Vector2D dir) : Entity(pos), Alive(maxHp, Hp), AMovable(dir) {
		std::cout << "Player just created at x = " << GetPos().x << " and y = " << GetPos().y << " with " << GetMaxHp() << " with direction x = " << GetDirection().x << " and y = " << GetDirection().y << std::endl;
	}


	void TakeDamage(float dmg) override;
	void Move() override;
	void Attack(Alive* other) override;
};

