#include "FirstScene.h"
#include"Plant.h"
#include"Zombi.h"

void FirstScene::OnInitialize()
{
	int cequetuveux = 900 / 3 / 2;
	plant1 = CreateEntity<Plant>(50, sf::Color::Green);
	plant1->SetPosition(100, cequetuveux);
	plant1->SetRigidBody(true);

	zombie1 = CreateEntity<Zombie>(50, sf::Color::Red);
	zombie1->SetPosition(600, cequetuveux);
	zombie1->SetRigidBody(true);

}

void FirstScene::TrySetSelectedEntity(Plant* pEntity, int x, int y)
{
}

void FirstScene::TrySetSelectedEntity(Zombie* pEntity, int x, int y)
{
}

void FirstScene::OnEvent(const sf::Event& event)
{
}

void FirstScene::OnUpdate()
{
}
