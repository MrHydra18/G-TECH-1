#pragma once
#include "Charactere.h"
#include "Ennemi.h"

class GameManager;

class GameState
{
public:
    bool inCombat;
    bool Menu(Charactere* player, GameManager* gameManager);
    void UseInventoryItem(Charactere* player, GameManager* gameManager);
    void Shop(Charactere* player, GameManager* gameManager);
    void Combat(Charactere* player, GameManager* game);
};