#include "PlantState.h"
#include "Plant.h"
#include "Bullet.h"

bool IdlePlantState::CanTransitionFrom(Plant* plant, int currentState)
{
	switch ((Plant::State)currentState)
	{
	case Plant::State::Idle:
		return false;
	}

	return true;
}

void IdlePlantState::Start(Plant* plant)
{
	std::cout << "State Idle\n";
}

void ShootingPlantState::Start(Plant* plant)
{
	m_timer = m_duration;
	plant->Shoot();
}

void ShootingPlantState::Update(Plant* plant, float dt)
{
	m_timer -= dt;

	if (m_timer > 0)
		return;

	plant->TryTransitionTo(Plant::State::Idle);
}

bool ShootingPlantState::CanTransitionFrom(Plant* plant, int currentState)
{
	switch ((Plant::State)currentState)
	{
	case Plant::State::Shooting:
		return false;
	case Plant::State::Reloading:
		return false;
	case Plant::State::Unloading:
		return false;
	}

	return true;
}

void ReloadingPlantState::Start(Plant* plant)
{
	m_timer = m_duration;
	plant->Reload();
}

void ReloadingPlantState::Update(Plant* plant, float dt)
{
	m_timer -= dt;

	if (m_timer > 0)
		return;

	plant->TryTransitionTo(Plant::State::Idle);
}

bool ReloadingPlantState::CanTransitionFrom(Plant* plant, int currentState)
{
	switch ((Plant::State)currentState)
	{
	case Plant::State::Shooting:
		return false;
	case Plant::State::Reloading:
		return false;
	case Plant::State::Unloading:
		return false;
	}

	return true;
}