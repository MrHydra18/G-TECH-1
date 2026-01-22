#include "Hero.h"
#include "Item.h"
#include "Charactere.h"
#include <iostream>

int Hero::Attack()
{
    //Calcul des degats que peut faire le joueur
    int damage = 10 + (GetLevel() - 1) * 3 + GetBonusEquipement();
    std::cout << "Slash! " << name << " fait " << damage << " pts de degat." << std::endl;
    return damage;
}