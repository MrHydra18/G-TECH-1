#pragma once
class Alive
{
protected:
	float maxHp;
	float Hp;

public:

	Alive(float MaxHealth, float Health) : maxHp(MaxHealth), Hp(Health) {}

	virtual float GetMaxHp() { return maxHp; }
	virtual float GetHp() { return Hp; }

	virtual void SetHp(float hp) { Hp = hp; }
	virtual void SetMaxHp(float maxhp) { maxHp = maxhp; }
	virtual void TakeDamage(float dmg) { Hp -= dmg; };
};

