#include "main.h"
#include "FirstScene.h"
#include <iostream>
#include "GameManager.h"

int main()
{
	GameManager* Instance = GameManager::Get();
	Instance->CreateWindow(1000, 900, "Tower Defense");
	Instance->LaunchScene<FirstScene>();
	return 0;
}
