#pragma once
#include "SceneManager.h"
#include  "Lib2D/Window.h"

//temp
#include <SDL.h>

class Application
{
private:
	Application() {}
	static Application* instance;

	Scene* ActualScene;

	Window* window;

	//temporaire
	Uint64 start = 0;
	Uint64 end = 0;
	Uint64 DeltaTime = 0;
	Uint64 TotalElapsed = 0 ;
	int FramCount = 0;

public :
	static Application* GetInstance();

	void Start();
	void Loop(bool* isRunning);
	void ShutDown();
};

