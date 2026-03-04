#include "Mage.h"
#include <iostream>

int Mage::Attack()
{
    //Calcul des degats que peut faire le joueur
    int damage = 15 + (GetLevel() - 1) * 4 + GetBonusEquipement();
    std::cout << "Boule de feu! " << name << " fait " << damage << " pts de degat magique." << std::endl;
    return damage;
}