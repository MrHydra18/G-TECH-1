#pragma once
#include "Charactere.h"

class Hero : public Charactere
{
public:

    Hero(const std::string& n, int hp, int ninerito, int exp) : Charactere(n, hp, ninerito, exp) {}

    int Attack() override;
};