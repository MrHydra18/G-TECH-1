#pragma once
#include "Charactere.h"
#include "Ennemi.h"
#include <vector>
#include<iostream>
#include <string>

class GameManager
{
private:
    std::vector<std::unique_ptr<Charactere>> characters;
    std::vector<std::unique_ptr<Ennemi>> ennemies;

public:
    int turn;
    bool isRuning;
    void Initialize();
    void AddItem(std::unique_ptr<Charactere> c);
    void AddEnemy(std::unique_ptr<Ennemi> e);
    int Attack();
    void Loop();
    static int AskInt(int min, int max, const std::string msg = "");
    void Shutdown();

    int GetEnemiesCount() const { return static_cast<int>(ennemies.size()); }
    Ennemi* GetEnemy(int index) {
        if (index >= 0 && index < static_cast<int>(ennemies.size())) {
            return ennemies[index].get();
        }
        return nullptr;
    }
};