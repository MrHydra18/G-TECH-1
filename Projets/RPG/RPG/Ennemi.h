#pragma once
#include <string>
#include <vector>

class Ennemi
{
protected:
	std::string name;
	int maxHp;
	int hp;
	int minGold;
	int maxGold;
	int damage;
	int exp;
	int lvl;

public:
	Ennemi(const std::string n, int maxHp, int minG, int maxG, int xp, int dmg) : name(n), maxHp(maxHp), hp(maxHp), minGold(minG), maxGold(maxG), exp(xp), damage(dmg) { GenerateRandomLevel(); };
	virtual ~Ennemi() = default;

	int Attack();
	void TakeDamage(int dmg);
	int GetGoldDrop();
	void ResetHp();
	int GetExpDrop();
	void GenerateRandomLevel();

	int GetLevel() const { return lvl; }
	std::string GetName() const { return name; }
	int GetHp() const { return hp; }
	bool IsDead() const { return hp <= 0; }
};