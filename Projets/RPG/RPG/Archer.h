#pragma once
#include "Charactere.h"
#include "Item.h"
#include <iostream>

class Archer : public Charactere
{
public:
	Archer(std::string n, int maxHp, int ninerito, int exp) : Charactere(n, maxHp, ninerito, exp) {}

	int Attack() override;
};