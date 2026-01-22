#pragma once

struct Grid
{
	char cells[3][3];
};

void Initialize(Grid* grid);

void Print(const Grid* grid);

bool SetCell(Grid* grid, int row, int col, char symbol);

bool IsWin(const Grid* grid, char symbol);

bool IsFull(const Grid* grid);
