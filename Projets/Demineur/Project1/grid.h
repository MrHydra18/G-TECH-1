#pragma once
#include "cell.h"

struct Grid
{
	int lineCount;
	int colCount;
	int mineCount;
	Cell* map;
};

void Initialize(Grid* grid, int nbrLignes, int nbrColones, int nbrMines);

void PrintTab(Grid* grid);

int CalculatePos(const Grid* grid, int row, int col);

void GenerateBomb(Grid* grid);

void CountMinesAdj(Grid* grid);

void RevealEmptyCells(Grid* grid, int x, int y);