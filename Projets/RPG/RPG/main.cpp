#include "Item.h"
#include "Charactere.h"
#include "GameManager.h"
#include <iostream>
#include <string>


int main()
{
	GameManager game;
	//On Initialise le jeu puis on rentre dans la boucle et quand on sort de la dernière on ferme le jeu
	game.Initialize();
	game.Loop();
	game.Shutdown();
	return 0;
}

