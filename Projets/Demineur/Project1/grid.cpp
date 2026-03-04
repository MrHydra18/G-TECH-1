#include "grid.h"
#include "cell.h"
#include <iostream>
#include <cstdlib>


void Initialize(Grid* grid, int lineCount, int colCount, int mineCount)
{
    grid->lineCount = lineCount;
    grid->colCount = colCount;
    grid->mineCount = mineCount;

    int total = lineCount * colCount;
    grid->map = new Cell[total];

    for (int i = 0; i < total; ++i) {
        grid->map[i] = Cell();
    }
}

int CalculatePos(const Grid* grid, int row, int col)
{
    return row * grid->colCount + col;
}

void RevealEmptyCells(Grid* grid, int x, int y)
{
    if (x < 0 || x >= grid->lineCount || y < 0 || y >= grid->colCount)
        return;

    int pos = CalculatePos(grid, x, y);
    Cell& cell = grid->map[pos];

    if (cell.IsReveal || cell.IsMine || cell.IsFlag)
        return;

    if (cell.MinesAdj > 0)
        std::cout << cell.MinesAdj;

    cell.IsReveal = true;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int newX = x + dx;
            int newY = y + dy;

            if (cell.MinesAdj == 0 )
            RevealEmptyCells(grid, newX, newY);
        }
    }
}




void PrintTab(Grid* grid)
{
    std::cout << "  ";
    for (int i = 0; i < grid->colCount; i++)
        std::cout << "   " << i;
    std::cout << "\n";

    for (int i = 0; i < grid->lineCount; i++)
    {
        std::cout << "   ";
        for (int j = 0; j < grid->colCount; j++)
            std::cout << "+---";
        std::cout << "+\n";

        std::cout << i << " ";
        for (int j = 0; j < grid->colCount; j++)
        {
            std::cout << " | ";
            int pos = CalculatePos(grid, i, j);

            if (pos >= 0 && pos < grid->lineCount * grid->colCount)
            {
                Cell cell = grid->map[pos];

                if (cell.IsReveal)
                {
                    if (cell.IsMine)
                        std::cout << "*";
                    else if (cell.MinesAdj > 0)
                        std::cout << cell.MinesAdj;
                    else
                        std::cout << "0";
                }
                else if (cell.IsFlag)
                {
                    std::cout << "F";
                }
                else
                {
                    std::cout << " ";
                }
            }
        }

        std::cout << " |\n";
    }

    std::cout << "   ";
    for (int j = 0; j < grid->colCount; j++)
        std::cout << "+---";
    std::cout << "+\n";
}


void GenerateBomb(Grid* grid)
{
    srand(time(NULL));

    int totalCells = grid->lineCount * grid->colCount;
    int nbrBomb = (int)(totalCells * 0.15f);
    grid->mineCount = nbrBomb;

    for (int i = 0; i < nbrBomb; i++)
    {
        int pos = rand() % totalCells;
        if (grid->map[pos].IsMine)
            continue;
        else
            grid->map[pos].IsMine = true;
    }
}

void CountMinesAdj(Grid* grid)
{
    for (int row = 0; row < grid->lineCount; row++)
    {
        for (int col = 0; col < grid->colCount; col++)
        {
            int pos = CalculatePos(grid, row, col);

            if (grid->map[pos].IsMine)
                continue;

            int mineCount = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                        continue;

                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < grid->lineCount &&
                        newCol >= 0 && newCol < grid->colCount)
                    {
                        int neighborPos = CalculatePos(grid, newRow, newCol);
                        if (grid->map[neighborPos].IsMine)
                            mineCount++;
                    }
                }
            }

            grid->map[pos].MinesAdj = mineCount;
        }
    }
}