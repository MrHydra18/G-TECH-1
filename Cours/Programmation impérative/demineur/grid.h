#pragma once
#include "cell.h"

struct Grid
{
	int lineCount;
	int colCount;
	int mineCount;
	Cell* map;
};

void Initialize(Grid* grid, int linesCount, int colCount, int mineCount);

void PrintTab(const Grid* grid);

int CalculatePos(const Grid* grid, int row, int col);

void GenerateBomb(Grid* grid);

int GameLevel(Grid* grid);
