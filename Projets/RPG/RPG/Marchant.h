#pragma once
#include "Charactere.h"
#include "Item.h"
#include <vector>

class Marchant : public Charactere
{
private:
    std::vector<std::pair<Item, int>> shopInventory; 

public:
    Marchant(std::string n, int maxHp, int ninerito, int exp);
    ~Marchant() = default;

    int Attack() override;
    void AddItemToShop(const Item& item, int price);
    void DisplayShop(const Charactere* player) const; 
    bool SellItem(Charactere* buyer, int itemIndex);
    int GetItemPrice(int itemIndex) const;
    size_t GetShopSize() const { return shopInventory.size(); }
};