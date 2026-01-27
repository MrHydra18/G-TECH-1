#pragma once

#include "Debug.h"
#include "Scene.h"

class Plant;
class Zombi;

class FirstScene : public Scene
{
	Plant* plant1;
	Zombi* zombi1;


public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};