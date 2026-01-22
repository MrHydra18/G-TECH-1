#include <iostream>
#include <cstdlib>
#include "grid.h"
#include "cell.h"


int AskInt(int min, int max, const char* msg = "", bool isBorned = true) {

    int value;
    do {
        if (msg == "") {
            if (isBorned) std::cout << "Entrez une valeur entre " << min << " et " << max << "." << std::endl;
            else std::cout << "Veuillez entrer un nombre." << std::endl;
        }
        else std::cout << msg << std::endl;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Merci d'entrer un nombre." << std::endl;
            continue;
        }
    } while (isBorned ? (value < min || value > max) : false);
    return value;
}

int GenerateRandomNumber(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

int main()
{
    Grid grid;
    int lvl = GameLevel(&grid);
    int size = grid.lineCount * grid.colCount;
    grid.map = new Cell[size];
    PrintTab(&grid);
}
