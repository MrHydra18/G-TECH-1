#include "Scene.h"

#include "GameManager.h"

void Scene::NextFrame()
{
	mpGameManager->SetDeltaTime(10000);
}

void Scene::SetTimeMultiplicator(float _timeMultiplicator)
{
	mpGameManager->SetTimeMultiplicator(_timeMultiplicator);
}

float Scene::GetTimeMultiplicator() const
{
	return mpGameManager->GetTimeMultiplicator();
}

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->GetDeltaTime();
}
