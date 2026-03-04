#include "Charactere.h"
#include <iostream>
// Classe abstraite

//Initialisation des differents personnages
Charactere::Charactere(std::string n, int maxHp, int ninerito, int exp) : name(n), hp(maxHp), maxHp(maxHp), money(ninerito), exp(exp), level(1), BonusEquipement(0){}


//Calcul des degats reçus
void Charactere::TakeDamage(int damage)
{
    hp -= damage;
    if (hp < 0) hp = 0;
}

//Calcul du soin
void Charactere::Heal(int amount)
{
    hp += amount;
    if (hp > maxHp) hp = maxHp;
    std::cout << name << " recupere " << amount << " PV! (PV actuels: " << hp << "/" << maxHp << ")" << std::endl;
}


//Affichage des stats
void Charactere::DisplayStatus() const
{
    std::cout << "\n=== Statut de " << name << " ===" << std::endl;
    std::cout << "Niveau: " << level << std::endl;
    std::cout << "PV: " << hp << "/" << maxHp << std::endl;
    std::cout << "Argent: " << money << " pieces d'or" << std::endl;
    std::cout << "Experience: " << exp << "/" << ExpNextLevel() << " XP" << std::endl;
    std::cout << "Bonus d'arme equipe: +" << BonusEquipement << " degats" << std::endl;
    std::cout << "========================\n" << std::endl;
}

//Affichage de l'inventaire
void Charactere::DisplayInventory() const
{
    std::cout << "\n=== Inventaire de " << name << " ===" << std::endl;

    if (inventory.empty())
    {
        std::cout << "Votre inventaire est vide." << std::endl;
        return;
    }

    for (size_t i = 0; i < inventory.size(); ++i)
    {
        std::cout << i + 1 << ". ";
        inventory[i].Display();
    }
}

//Ajout d'un item a l'inventaire
void Charactere::AddItem(const Item& item)
{
    inventory.push_back(item);
}

//Utilisation d'un item
bool Charactere::UseItem(int index)
{
    Item& item = inventory[index];

    if (item.GetType() == ItemType::CONSUMABLE)
    {
        int healAmount = item.GetHealAmount();
        if (healAmount > 0)
        {
            Heal(healAmount);
            //Apres utilisation l'Item s'efface
            inventory.erase(inventory.begin() + index);
            return true;
        }
    }
    else if (item.GetType() == ItemType::WEAPON)
    {
        int damageBonus = item.GetDamageBonus();
        BonusEquipement = damageBonus;
        std::cout << "\n" << name << " equipe " << item.GetName() << "! Bonus de degats: +" << damageBonus << std::endl;
        inventory.erase(inventory.begin() + index);
        return true;
    }

    std::cout << "Cet objet ne peut pas etre utilise maintenant." << std::endl;
    return false;
}

//Ajouter de l'argent
void Charactere::AddMoney(int amount)
{
    money += amount;
}

//Ajouter de l'experience
void Charactere::AddExp(int amount)
{
    exp += amount;
    int expNeeded = ExpNextLevel();

    while (exp >= expNeeded)
    {
        LevelUp();
        expNeeded = ExpNextLevel();
    }
}

//Fonction pour monter de niveau
void Charactere::LevelUp()
{
    //On remet l'exp a 0 apres chaque montée
    exp -= ExpNextLevel();
    level++;
    int hpIncrease = maxHp * 1.2;
    maxHp = hpIncrease;
    hp = maxHp;

    std::cout << "\n======== LEVEL UP! ========" << std::endl;
    std::cout << name << " est maintenant niveau " << level << "!" << std::endl;
    std::cout << "PV maximum augmentes a " << maxHp << std::endl;
    std::cout << "PV completement restaures!" << std::endl;
    std::cout << "===========================\n" << std::endl;
}

//Calcul de combien exp nous faut pour monter de niveau
int Charactere::ExpNextLevel() const
{
    int baseExp = 20;
    int maxExp = baseExp;

    for (int i = 1; i < level; i++)
    {
        maxExp = maxExp * 1.3;
    }
    return maxExp;
}

//Fonction pour remettre tous les PV
void Charactere::ResetHp()
{
    hp = maxHp;
}