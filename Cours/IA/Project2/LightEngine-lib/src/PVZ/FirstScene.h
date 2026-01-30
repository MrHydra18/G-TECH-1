#pragma once

#include "Debug.h"
#include "Scene.h"

class Plant;
class Zombie;

class FirstScene : public Scene
{

	int nb_lanes = 4;
	std::vector<Plant*> m_plants;

private:
	void TrySetSelectedEntity(Plant* pEntity, int x, int y) {}
	void TrySetSelectedEntity(Zombie* pEntity, int x, int y) {}

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	friend Plant;
};