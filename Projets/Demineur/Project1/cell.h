#pragma once
struct Cell
{
	bool IsMine;
	bool IsReveal;
	bool IsFlag;
	int MinesAdj;
};

void Initialize(Cell* cell, bool IsMine, bool IsReveal, bool IsFlag, int MinesAdj);
