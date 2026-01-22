#include "Grid.h"

#include <iostream>

// EX1
void Initialize(Grid* grid) 
{
	// TODO: Initialiser la grille en mettant des espaces dans toutes les cellules

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			grid->cells[i][j] = ' ';
		}
	}
}

// EX2
void Print(const Grid* grid) 
{
	system("cls"); // rafraissement d'écran

	// TODO: Afficher la grille dans la console
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << "[" << grid->cells[i][j] << "]";
		}
		std::cout << "" << std::endl;
	}

	// Exemple d'affichage attendu :
	// [ ][ ][ ]
	// [ ][X][ ]
	// [O][ ][ ]
}

// EX3
bool SetCell(Grid* grid, int row, int col, char symbol) 
{
	// TODO: Mettre à jour la cellule spécifiée avec le symbole donné
	// Assurez vous que la cellule choisie soit vide 
	// Retourner true si c'est le cas, sinon false
	if (grid->cells[row][col] = ' ')
	{
		grid->cells[row][col] = symbol;
		return true;
	}

	return false;
}

// EX4
bool IsWin(const Grid* grid, char symbol) 
{
	// TODO: Vérifier si le symbole donné a une ligne gagnante dans la grille (horizontale, verticale ou diagonale)
	// Retourner true si le symbole a gagné, sinon false

	for (int i = 0; i < 3; ++i)
	{
		if (grid->cells[i][0] == symbol && grid->cells[i][1] == symbol && grid->cells[i][2] == symbol)
			return true;
	}

	for (int j = 0; j < 3; ++j)
	{
		if (grid->cells[0][j] == symbol && grid->cells[1][j] == symbol && grid->cells[2][j] == symbol)
			return true;
	}

	if (grid->cells[0][0] == symbol && grid->cells[1][1] == symbol && grid->cells[2][2] == symbol)
		return true;

	if (grid->cells[0][2] == symbol && grid->cells[1][1] == symbol && grid->cells[0][2] == symbol)
		return true;

	return false;
}

// EX5
bool IsFull(const Grid* grid) 
{
	// TODO: Vérifier si toutes les cellules de la grille sont remplies
	// Retourner true si la grille est pleine, sinon false

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (grid->cells[i][j] == ' ')
				return false;
		}
	}

	return true;

	//BONUS : 
	// proposer une méthode plus optimisée pour savoir quand la grille est pleine
	// Faites toutes les modifications que vous jugez nécessaires sur l'architecture déjà en place
}
