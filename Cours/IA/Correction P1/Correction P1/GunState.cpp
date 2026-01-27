#include "GunState.h"

#include "Gun.h"

bool IdleGunState::CanTransitionFrom(Gun* gun, int currentState)
{
	switch ((Gun::State)currentState)
	{
	case Gun::State::Idle: 
		return false;
	}

	return true;
}

void ShootingGunState::Start(Gun* gun)
{
	m_timer = m_duration;
	gun->m_ammo--;
}

void ShootingGunState::Update(Gun* gun, float dt)
{
	m_timer -= dt;

	if (m_timer > 0)
		return;

	gun->TryTransitionTo(Gun::State::Idle);
}

bool ShootingGunState::CanTransitionFrom(Gun* gun, int currentState)
{
	switch ((Gun::State)currentState)
	{
	case Gun::State::Shooting:
		return false;
	case Gun::State::Reloading:
		return false;
	case Gun::State::Unloading:
		return false;
	}

	if (gun->m_ammo <= 0)
		return false;

	return true;
}

void ReloadingGunState::Start(Gun* gun)
{
	m_timer = m_duration;
}

void ReloadingGunState::Update(Gun* gun, float dt)
{
	m_timer -= dt;

	if (m_timer > 0)
		return;

	gun->m_ammo = gun->m_capacity;

	gun->TryTransitionTo(Gun::State::Idle);
}

bool ReloadingGunState::CanTransitionFrom(Gun* gun, int currentState)
{
	switch ((Gun::State)currentState)
	{
	case Gun::State::Shooting:
		return false;
	case Gun::State::Reloading:
		return false;
	case Gun::State::Unloading:
		return false;
	}

	if (gun->m_ammo >= gun->m_capacity)
		return false;

	return true;
}

void UnloadingGunState::Start(Gun* gun)
{
	m_timer = m_duration;
}

void UnloadingGunState::Update(Gun* gun, float dt)
{
	m_timer -= dt;

	if (m_timer > 0)
		return;

	gun->m_ammo = 0;

	gun->TryTransitionTo(Gun::State::Idle);
}

bool UnloadingGunState::CanTransitionFrom(Gun* gun, int currentState)
{
	switch ((Gun::State)currentState)
	{
	case Gun::State::Shooting:
		return false;
	case Gun::State::Reloading:
		return false;
	case Gun::State::Unloading:
		return false;
	}

	if (gun->m_ammo <= 0)
		return false;

	return true;
}