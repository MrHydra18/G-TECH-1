#include "Ennemi.h"
#include "RandomManager.h"
#include <iostream>

//Calcul des degats
int Ennemi::Attack()
{
	int damage = 5;
	damage = damage + (lvl - 1) * 2;
	return damage;
}

//Degats reçus
void Ennemi::TakeDamage(int dmg)
{
	hp = hp - dmg;
	if (hp < 0)
		hp = 0;
}

//Combien de pieces d'or ils droppent (c'est aleatoire entre deux limites)
int Ennemi::GetGoldDrop()
{
	return RandomManager::GenerateRandomNumber(minGold, maxGold);
}

//Combien d'exp ils droppent (cette ci n'est pas aleatoire)
int Ennemi::GetExpDrop()
{
	return exp;
}

//Remmettre tous les PV pour eviter quelques bugs
void Ennemi::ResetHp()
{
	hp = maxHp;
}

//Generation aleatoire du niveau du monstre
void Ennemi::GenerateRandomLevel()
{
	lvl = RandomManager::GenerateRandomNumber(1, 5);

	maxHp = maxHp + (lvl - 1) * 3;
	hp = maxHp;
	minGold = minGold + (lvl - 1) * 2;
	maxGold = maxGold + (lvl - 1) * 2;
} 