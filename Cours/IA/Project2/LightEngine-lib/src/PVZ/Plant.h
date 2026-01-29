#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include<iostream>


class Plant : public Entity
{

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

	StateMachine<Plant> m_stateMachine;


public:

	Plant();

	void Update(float dt);

	void Shoot();

	void Reload();

	void TryTransitionTo(State state);
	void OnCollision(Entity* other) override;
	void OnInitialize() override;


	friend class IdleGunState;
	friend class ShootingGunState;
	friend class ReloadingGunState;
	friend class UnloadingGunState;
};

