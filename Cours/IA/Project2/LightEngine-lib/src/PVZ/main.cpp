#include "pch.h"
#include "main.h"
#include <iostream>
#include "GameManager.h"

int main()
{
	GameManager* Instance = GameManager::Get();
	Instance->CreateWindow(500, 500, "Tower Defense");
	Instance->LaunchScene<TowerDefense>();
	return 0;
}
