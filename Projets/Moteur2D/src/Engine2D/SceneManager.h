#pragma once
#include "Scene.h"

class SceneManager
{
protected:
	SceneManager() {}
	static SceneManager* instance;
	std::vector<Scene*> AllScene;
	Scene* ActualScene;

public:
	static SceneManager* GetInstance();
	void InitAllScene(); // call the new scene fonction here
	Scene* DefineActualScene();

	float srand(int min, int max);
	int AskInt(const char* msg);

	Scene* GetActualScene() { return ActualScene; }

	//add new scene fonction here:
	void InitScene1();
	void InitScene2();
	void InitScene3();

};
