#include "Item.h"
#include <iostream>

void Item::Display() const
{
    std::cout << "- " << name << " (Valeur: " << value << ") - " << description;

    //Verification si l'objet est une arme ou une potion 
    if (type == ItemType::CONSUMABLE && healAmount > 0)
    {
        std::cout << " [Soin: " << healAmount << " PV]";
    }
    else if (type == ItemType::WEAPON && damageBonus > 0)
    {
        std::cout << " [Bonus degats: +" << damageBonus << "]";
    }

    std::cout << std::endl;
}