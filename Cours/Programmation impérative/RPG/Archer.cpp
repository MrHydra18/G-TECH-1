#include "Archer.h"
#include <iostream>

int Archer::Attack()
{
    //Calcul des dégats que peut faire le joueur
    int damage = 12 + (GetLevel() - 1) * 3 + GetBonusEquipement();
    std::cout << "Tir de fleche! " << name << " fait " << damage << " pts de degat." << std::endl;
    return damage;
}