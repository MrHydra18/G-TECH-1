#pragma once
#include <string>

enum class ItemType
{
    CONSUMABLE,  
    WEAPON,
};

class Item
{
private:
    std::string name;
    int value;
    std::string description;
    ItemType type;
    int healAmount;
    int damageBonus;

public:
    Item(std::string n, int val, std::string desc, ItemType t = ItemType::CONSUMABLE, int heal = 0, int dmg = 0) : name(n), value(val), description(desc), type(t), healAmount(heal), damageBonus(dmg) {}

    void Display() const;

    std::string GetName() const { return name; }
    int GetValue() const { return value; }
    std::string GetDescription() const { return description; }
    ItemType GetType() const { return type; }
    int GetHealAmount() const { return healAmount; }
    int GetDamageBonus() const { return damageBonus; }
};