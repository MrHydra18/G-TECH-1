#include "Scene.h"

void Scene::UpdateAll()
{
	int size = EntityStock.size();
	for (int i = 0; i <= size-1; i++)
		EntityStock[i]->Update();
}

void Scene::Draw(Window* win)
{
	int size = EntityStock.size();
	for (int i = 0; i <= size - 1; i++)
		EntityStock[i]->Draw(win);
}

void Scene::ChangeColor(Window* win)
{
	
}

void Scene::DeletAll()
{
	int size = EntityStock.size();
	for (int i = 0; i <= size - 1; i++)
		EntityStock[i]->Delet();
}
