#include "Gun.h"

#include "GunState.h"

Gun::Gun()
{
	m_ammo = m_capacity;

	m_stateMachine.Add(new IdleGunState());
	m_stateMachine.Add(new ShootingGunState());
	m_stateMachine.Add(new ReloadingGunState());
	m_stateMachine.Add(new UnloadingGunState());
}

void Gun::Update(float dt)
{
	m_stateMachine.Update(this, dt);
}

void Gun::Shoot()
{
	TryTransitionTo(State::Shooting);
}

void Gun::Reload()
{
	TryTransitionTo(State::Reloading);
}

void Gun::TryTransitionTo(State state)
{
	m_stateMachine.TryTransitionTo(this, (int)state);
}