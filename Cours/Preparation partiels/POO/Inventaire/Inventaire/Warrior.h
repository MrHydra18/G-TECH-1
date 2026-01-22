#pragma once
#include "Character.h"
class Warrior : public Character
{
public:

	Warrior(int hp, int maxHp, std::string n) : Character(hp, maxHp, n) {}

	void heal(int amount) override;
	void DisplayStats() override;
};

