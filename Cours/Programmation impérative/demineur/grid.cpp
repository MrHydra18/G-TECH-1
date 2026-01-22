#include "grid.h"
#include "cell.h"
#include <iostream>
#include <cstdlib>



void Initialize(Grid* grid, int linesCount, int colCount, int mineCount)
{
    grid->lineCount = linesCount;
    grid->colCount = colCount;
    grid->mineCount = mineCount;
}


int CalculatePos(const Grid* grid, int row, int col)
{
    return row * grid->colCount + col;
}

void GenerateBomb(Grid* grid)
{
    srand(time(NULL));
    int nbrBomb = grid->colCount * grid->lineCount * 0.15f;
    for (int i = 0; i < nbrBomb; i++)
    {
        int  pos;

    }
}

void PrintTab(const Grid* grid)
{
    std::cout << "  ";
    for (int i = 0; i < grid->lineCount; i++) std::cout << "   " << i;
    std::cout << "\n";

    for (int i = 0; i < grid->lineCount; i++) 
    {
        std::cout << "   ";

        for (int j = 0; j < grid->colCount; j++) 
        {
            std::cout << "+---";
        }
        std::cout << "+\n";
        std::cout << i << " ";

        for (int j = 0; j < grid->colCount; j++) 
        {
            std::cout << " | ";
            int pos = CalculatePos(grid, i, j);

            if (grid->map[pos].IsReveal = true) 
            {
                if (grid->map[pos].IsReveal) std::cout << " ";


                else std::cout << grid->map[pos].MinesAdj;
            }
            else std::cout << " ";
        }
        std::cout << " |\n";

    }
    std::cout << "   ";
    for (int j = 0; j < grid->colCount; j++) {
        std::cout << "+---";
    }
    std::cout << "+\n";
}

int GameLevel(Grid* grid)
{
    int lvl;
    std::cout << "Selectionnez un niveau de jeu. Easy (9 x 9) = 1 / Medium (16 x 16) = 2 / Hard (30 x 16) = 3 / Personalized = 4" << std::endl;
    std::cin >> lvl;

    switch (lvl)
    {
    case 1:
        grid->lineCount = 9;
        grid->colCount = 9;
        break;

    case 2:
        grid->lineCount = 16;
        grid->colCount = 16;
        break;

    case 3:
        grid->lineCount = 16;
        grid->colCount = 30;
        break;

    case 4:
        std::cout << "Veuillez entrer le nombre de lignes :" << std::endl;
        std::cin >> grid->lineCount;
        std::cout << "Veuillez entrer le nombre de colonnes :" << std::endl;
        std::cin >> grid->colCount;
        break;
    }

    return lvl;
}
