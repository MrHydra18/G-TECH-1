#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Charactere
{
protected:
    std::string name;
    int hp;
    int maxHp;
    int money;
    int exp;
    int maxExp;
    int level;
    std::vector<Item> inventory;
    int BonusEquipement; // Bonus de l'arme équipée

public:
    Charactere(std::string n, int maxHp, int ninerito, int exp);
    virtual ~Charactere() = default;

    virtual int Attack() = 0;
    void TakeDamage(int damage);
    void Heal(int amount);
    void DisplayStatus() const;
    void DisplayInventory() const;
    void AddItem(const Item& item);
    bool UseItem(int index);
    int ExpNextLevel() const;
    void AddMoney(int amount);
    void AddExp(int amount);
    void LevelUp();
    void ResetHp();

    // Getters
    std::string GetName() const { return name; }
    int GetHp() const { return hp; }
    int GetMaxHp() const { return maxHp; }
    int GetMoney() const { return money; }
    int GetExp() const { return exp; }
    int GetLevel() const { return level; }
    size_t GetInventorySize() const { return inventory.size(); }
    int GetBonusEquipement() const { return BonusEquipement; }
};