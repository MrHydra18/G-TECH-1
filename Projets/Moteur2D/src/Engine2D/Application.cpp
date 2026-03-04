#include <iostream>
#include "Timer.h"
#include "Application.h"

Application* Application::instance = nullptr;

Application* Application::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Application();
	}
	return instance;
}

void Application::Start()
{
	window = new Window();
	window->Init();
	SceneManager::GetInstance()->InitAllScene();
	ActualScene = SceneManager::GetInstance()->DefineActualScene();
}

void Application::Loop(bool* isRunning)
{
	srand(time(NULL));
	InputManager* IM = InputManager::GetInstance();
	Timer timer;

	while (*isRunning)
	{
		timer.Start();
		window->WindowManager();

		*isRunning = IM->update();

		if (IM->isQuit())
		{
			*isRunning = false;
		}

		ActualScene->UpdateAll();
		window->Draw(ActualScene);

		window->UpdateWindow();

		timer.End();

		window->CountTime(timer.Diff());
	}
	std::cout << "voulez-vous choisire une autre scene ? 0/1" << std::endl;
	std::cin >> *isRunning;

	if (*isRunning)
	{
		ActualScene = SceneManager::GetInstance()->DefineActualScene();
	}
	else
		ShutDown();
}

void Application::ShutDown()
{
	window->DestroyWindow();
	delete window;
	window = nullptr;
	ActualScene->DeletAll();
}
