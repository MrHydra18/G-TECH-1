#include "cell.h"


void Initialize(Cell* cell, bool IsMine, bool IsReveal, bool IsFlag, int MinesAdj)
{
	cell->IsFlag = IsFlag;
	cell->IsMine = IsMine;
	cell->IsReveal = IsReveal;
	cell->MinesAdj = MinesAdj;
}