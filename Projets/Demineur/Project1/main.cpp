#include <iostream>
#include <cstdlib>
#include "grid.h"
#include "cell.h"

int AskInt(int min, int max, const char* msg = "")
{
    int value;
    do {
        std::cout << msg << std::endl;
        std::cin >> value;
        if (value < min || value > max)
            std::cout << "La valeur est incompatible, veuillez la rentrer a nouveau." << std::endl;
    } while (value < min || value > max);
    return value;
}

int GameLevel(Grid* grid)
{
    int lvl = AskInt(1, 4, "Selectionnez un niveau de jeu. Easy (9x9)=1 / Medium (16x16)=2 / Hard (30x16)=3 / Personalise=4");
    switch (lvl)
    {
    case 1:
        grid->lineCount = 9;
        grid->colCount = 9;
        grid->mineCount = (int)(9 * 9 * 0.15f);
        break;
    case 2:
        grid->lineCount = 16;
        grid->colCount = 16;
        grid->mineCount = (int)(16 * 16 * 0.15f);
        break;
    case 3:
        grid->lineCount = 16;
        grid->colCount = 30;
        grid->mineCount = (int)(16 * 30 * 0.15f);
        break;
    case 4:
        grid->lineCount = AskInt(1, 64, "Nombre de lignes :");
        grid->colCount = AskInt(1, 64, "Nombre de colonnes :");
        grid->mineCount = (int)(grid->lineCount * grid->colCount * 0.15f);
        break;
    }
    return lvl;
}

void GamePlay(Grid* grid)
{
    bool playAgain = true;

    while (playAgain)
    {
        bool isPlaying = true;
        bool firstMove = true;

        GameLevel(grid);
        Initialize(grid, grid->lineCount, grid->colCount, grid->mineCount);

        int size = grid->lineCount * grid->colCount;

        if (firstMove)
        {
            int col = AskInt(0, grid->colCount - 1, "Quelle est l'abscisse de votre case ?");
            int row = AskInt(0, grid->lineCount - 1, "Quelle est l'ordonnee de votre case ?");
            GenerateBomb(grid);
            CountMinesAdj(grid);
            RevealEmptyCells(grid, row, col);
            firstMove = false;
        }

        while (isPlaying)
        {
            system("cls");
            PrintTab(grid);

            int col = AskInt(0, grid->colCount - 1, "Quelle est l'abscisse de votre case ?");
            int row = AskInt(0, grid->lineCount - 1, "Quelle est l'ordonnee de votre case ?");
            int choix = AskInt(1, 2, "Reveal=1 / Flag=2 ?");

            int pos = CalculatePos(grid, row, col);

            if (choix == 2)
            {
                grid->map[pos].IsFlag = !grid->map[pos].IsFlag;
                continue;
            }

            if (grid->map[pos].IsMine && !grid->map[pos].IsFlag)
            {
                for (int i = 0; i < size; ++i)
                {
                    if (grid->map[i].IsMine)
                        grid->map[i].IsReveal = true;
                }

                system("cls");
                PrintTab(grid);
                std::cout << " BOOM! Tu as touche une mine. Game Over." << std::endl;
                isPlaying = false;
                break;
            }
            else
            {
                RevealEmptyCells(grid, row, col);
            }

            int revealed = 0, totalNonMines = 0;
            for (int i = 0; i < size; ++i)
            {
                if (!grid->map[i].IsMine)
                {
                    totalNonMines++;
                    if (grid->map[i].IsReveal)
                        revealed++;
                }
            }

            if (revealed == totalNonMines)
            {
                system("cls");
                PrintTab(grid);
                std::cout << "Felicitations! Tu as gagne!" << std::endl;
                isPlaying = false;
            }
        }

        int again = AskInt(1, 2, "Rejouer? Oui = 1 / Non = 2");
        if (again != 1)
            playAgain = false;

        delete[] grid->map;
        grid->map = nullptr;
    }
}

int main()
{
    Grid grid;
    GamePlay(&grid);
    return 0;
}