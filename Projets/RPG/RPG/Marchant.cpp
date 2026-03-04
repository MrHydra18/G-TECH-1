#include "Marchant.h"
#include "Charactere.h"
#include <iostream>

Marchant::Marchant(std::string n, int maxHp, int ninerito, int exp) : Charactere(n, maxHp, ninerito, exp){}

//Fonction inutile mais obligatoire vu que marchant fais parties des characteres
int Marchant::Attack()
{
    std::cout << name << " refuse de se battre! C'est un marchand paisible." << std::endl;
    return 0;
}

//Ajouter un objet a la boutique
void Marchant::AddItemToShop(const Item& item, int price)
{
    shopInventory.push_back(std::make_pair(item, price));
}

//Affichage de la boutique
void Marchant::DisplayShop(const Charactere* player) const
{
    std::cout << "\n=== Boutique de " << name << " ===" << std::endl;
    std::cout << "Votre argent: " << player->GetMoney() << " pieces d'or" << std::endl;
    std::cout << "================================" << std::endl;

    //Si la boutique est vide on affiche qu'elle est vide
    if (shopInventory.empty())
    {
        std::cout << "La boutique est vide." << std::endl;
        return;
    }

    for (size_t i = 0; i < shopInventory.size(); ++i)
    {
        std::cout << i + 1 << ". ";
        shopInventory[i].first.Display();
        std::cout << "   Prix: " << shopInventory[i].second << " pieces d'or" << std::endl;
    }
}

//Fonction pour vendre les objets
bool Marchant::SellItem(Charactere* customer, int itemIndex)
{
    //Declaratio que le prix c'est la deuxième valeur d'un item
    int price = shopInventory[itemIndex].second;

    //Verification qu'on a l'argent suffisant
    if (customer->GetMoney() < price)
    {
        std::cout << "Vous n'avez pas assez d'argent! Il vous manque " << (price - customer->GetMoney()) << " pieces d'or." << std::endl;
        return false;
    }

    //On achete un objet en voyant son nom et il ajoute l'objet dans notre inventaire et enlève prix de l'argent qu'on a
    Item itemToBuy = shopInventory[itemIndex].first;
    customer->AddItem(itemToBuy);
    customer->AddMoney(-price);

    std::cout << "\nVous avez achete: " << itemToBuy.GetName() << " pour " << price << " pieces d'or!" << std::endl;

    return true;
}

//Avoir le prix d'un objet
int Marchant::GetItemPrice(int itemIndex) const
{
    if (itemIndex >= 0 && itemIndex < static_cast<int>(shopInventory.size()))
    {
        return shopInventory[itemIndex].second;
    }
    return 0;
}