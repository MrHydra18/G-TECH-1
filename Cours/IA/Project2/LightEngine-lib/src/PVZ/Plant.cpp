#include "Plant.h"
#include "Bullet.h"
#include "PlantState.h"

Plant::Plant()
{
	m_stateMachine.Add(new IdlePlantState());
	m_stateMachine.Add(new ShootingPlantState());
	m_stateMachine.Add(new ReloadingPlantState());
}

void Plant::OnCollision(Entity* other)
{
	std::cout << "Plant has collide\n";
}

void Plant::OnInitialize()
{
	SetTag(1);
}


void Plant::Update(float dt)
{
	m_stateMachine.Update(this, dt);
}

void Plant::Shoot()
{
	FirstScene* scene = GetScene<FirstScene>();

	int lane = scene->GetWindowHeight() / scene->nb_lanes / 2;

	Bullet* bullet = CreateEntity<Bullet>(scene->GetWindowHeight() / (scene->nb_lanes * 15), sf::Color::Magenta);
	bullet->SetPosition(150, lane * scene->GetWindowHeight() / scene->nb_lanes + scene->GetWindowHeight() / scene->nb_lanes / 2);
	bullet->SetDirection(1, 0, 200);

	std::cout << "Transition to shooting \n";

	TryTransitionTo(State::Idle);
}

void Plant::Reload()
{
	TryTransitionTo(State::Reloading);
	std::cout << "Transition to reload\n";
}

void Plant::TryTransitionTo(State state)
{
	m_stateMachine.TryTransitionTo(this, (int)state);
}