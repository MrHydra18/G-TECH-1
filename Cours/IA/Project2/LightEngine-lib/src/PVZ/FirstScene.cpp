#include "FirstScene.h"
#include"Plant.h"
#include "Bullet.h"
#include"Zombi.h"

void FirstScene::OnInitialize()
{

	int lane = GetWindowHeight() / nb_lanes / 2;
	
	for (int i = 0; i < nb_lanes; ++i)
	{
		Plant* plant = CreateEntity<Plant>(50, sf::Color::Green);
		plant->SetPosition(100, lane);
		lane += GetWindowHeight() / nb_lanes;
	}

}


void FirstScene::OnEvent(const sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Button::Left && event.type == event.MouseButtonPressed)
	{
		int lane = event.mouseButton.y / (GetWindowHeight() / nb_lanes);

		Zombie* zombie = CreateEntity<Zombie>(GetWindowHeight() / (nb_lanes * 11.5), sf::Color::Red);
		zombie->SetPosition(GetWindowWidth() + zombie->GetRadius() - 1, lane * GetWindowHeight() / nb_lanes + GetWindowHeight() / nb_lanes / 2);
		zombie->SetDirection(-1, 0, 200);

		Bullet* bullet = CreateEntity<Bullet>(GetWindowHeight() / (nb_lanes * 15), sf::Color::Magenta);
		bullet->SetPosition(150, lane * GetWindowHeight() / nb_lanes + GetWindowHeight() / nb_lanes / 2);
		bullet->SetDirection(1, 0, 200);
	}
}

void FirstScene::OnUpdate()
{
}
