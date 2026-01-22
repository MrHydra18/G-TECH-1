#pragma once
#include<string>
#include<iostream>

class Character
{
protected:
	int health;
	int maxHealth;
	std::string name;

public:
	Character(int hp, int MaxHp, std::string n) : health(hp), maxHealth(MaxHp), name(n) {}
	virtual ~Character() = default;

	virtual void heal(int amount) ;
	virtual void DisplayStats() ;
};