#pragma once

#include "StateMachine.h"

class Gun
{
	int m_ammo;
	int m_capacity = 6;

public:
	enum class State
	{
		Idle,
		Shooting,
		Reloading,
		Unloading,

		Count
	};

private:
	StateMachine<Gun> m_stateMachine;

public:
	Gun();

	void Update(float dt);

	void Shoot();

	void Reload();

	void TryTransitionTo(State state);

	friend class IdleGunState;
	friend class ShootingGunState;
	friend class ReloadingGunState;
	friend class UnloadingGunState;
};
