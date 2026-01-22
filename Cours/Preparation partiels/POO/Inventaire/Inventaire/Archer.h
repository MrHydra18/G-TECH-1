#pragma once
#include "Character.h"
class Archer : public Character
{
public:

	Archer(int hp, int maxHp, std::string n) : Character(hp, maxHp, n) {}

	void heal(int amount) override;
	void DisplayStats() override;
};

