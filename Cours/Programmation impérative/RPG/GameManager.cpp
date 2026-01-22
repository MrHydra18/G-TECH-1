#include "GameManager.h"
#include "GameState.h"
#include "Hero.h"
#include "Archer.h"
#include "Mage.h"
#include "Ennemi.h"
#include <iostream>
#include "Item.h"


//Initialisation, on ajoute juste les ennemies et on dit que la boucle de jeu est vraie
void GameManager::Initialize()
{
	AddEnemy(std::make_unique<Ennemi>("Goblin", 50, 20, 40, 5, 5));
	AddEnemy(std::make_unique<Ennemi>("Orc", 80, 25, 45, 15, 10));
	AddEnemy(std::make_unique<Ennemi>("Troll", 100, 30, 50, 25, 15));

	turn = 1;
	isRuning = true;
}

//Fonction pour eviter de me repeter a chaque fois qu'on doit faire un choix
int GameManager::AskInt(int min, int max, const std::string msg)
{
	int value;
	do {
		std::cout << msg << std::endl;
		std::cin >> value;
		if (value < min || value > max)
			std::cout << "\n La valeur est incompatible, veuillez la rentrer a nouveau." << std::endl;
	} while (value < min || value > max);
	return value;
}

//Ajoutter un objet a l'inventaire
void GameManager::AddItem(std::unique_ptr<Charactere> c)
{
	characters.push_back(std::move(c));
}

//Ajouter un ennemi
void GameManager::AddEnemy(std::unique_ptr<Ennemi> e)
{
	ennemies.push_back(std::move(e));
}

//Fonction pour attaquer (chaque classe a son propre attaque)
int GameManager::Attack()
{
	for (auto& c : characters)
		c->Attack();
	return 0;
}

//Fermeture du jeu
void GameManager::Shutdown()
{
	system("cls");
	std::cout << "\n Merci d'avoir joue a Valkyrium." << std::endl;
}

//Boucle de jeu
void GameManager::Loop()
{
	std::string name;

	std::cout << "=== Bienvenue dans le monde de Veloria ===" << std::endl;
	std::cout << "\n Quel est votre nom aventurier?" << std::endl;
	std::cin >> name;
	system("cls");

	int choice = AskInt(1, 3, "\n Choisissez votre classe : 1 = Hero / 2 = Mage / 3 = Archer ");

	std::unique_ptr<Charactere> player;
	system("cls");

	//Choix de la classe du perso
	switch (choice)
	{
	case 1:
		player = std::make_unique<Hero>(name, 100, 0, 0);
		player->AddItem(Item("Epee de bois", 1, "Une epee en bois", ItemType::WEAPON, 0, 5));
		player->AddItem(Item("Potion de soin", 10, "Restaure 10 PV", ItemType::CONSUMABLE, 10));
		std::cout << "\nVous avez choisi la classe Hero!" << std::endl;
		break;
	case 2:
		player = std::make_unique<Mage>(name, 100, 0, 0);
		player->AddItem(Item("Potion de soin", 10, "Restaure 10 PV", ItemType::CONSUMABLE, 10));
		player->AddItem(Item("Grande potion", 50, "Restaure 50 PV", ItemType::CONSUMABLE, 50));
		std::cout << "\nVous avez choisi la classe Mage!" << std::endl;
		break;
	case 3:
		player = std::make_unique<Archer>(name, 100, 0, 0);
		player->AddItem(Item("Arc", 1, "Un arc pour tirer des fleches", ItemType::WEAPON, 0, 10));
		player->AddItem(Item("Potion de soin", 10, "Restaure 10 PV", ItemType::CONSUMABLE, 10));
		std::cout << "\nVous avez choisi la classe Archer!" << std::endl;
		break;
	}

	while (isRuning)
	{
		GameState gameState;
		isRuning = gameState.Menu(player.get(), this);
	}
}