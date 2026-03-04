#include <iostream> 
#include "SceneManager.h"
#include "Scene.h"
#include "Application.h"
#include "Lib2D/Window.h"

#include "Game/Scene1.h"
#include "Game/Scene2.h"
#include "Game/Scene3.h"


SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SceneManager();
	}
	return instance;
}

int SceneManager::AskInt(const char* msg)
{
	int value = 0;
	std::cout << msg << std::endl;
	std::cin >> value;
	return value;
}

void SceneManager::InitAllScene()
{
	Scene1* scene1 = new Scene1("Test Coeur");
	Scene2* scene2 = new Scene2("Test DVD");
	Scene3* scene3 = new Scene3("Pong", W_HEIGHT, W_WIDTH);
	//call of the new scene :

	AllScene.push_back(scene1);
	AllScene.push_back(scene2);
	AllScene.push_back(scene3);
}

Scene* SceneManager::DefineActualScene()
{
	system("cls");
	std::cout << "scene actuellement charger : " << std::endl;
	for (int i = 0; i <= (AllScene.size() - 1); i++)
		std::cout << "- " << AllScene[i]->GetName() << " : " << (i) << std::endl;
	int choice = AskInt("quelle scene vouler vous choisire ? :");
	ActualScene = AllScene[choice];
	return ActualScene;
}


