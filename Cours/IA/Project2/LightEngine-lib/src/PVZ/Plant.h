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
	int m_lane;


public:

	Plant();

	void Update(float dt);

	void Shoot();

	void Reload();

	void TryTransitionTo(State state);
	void OnCollision(Entity* other) override;
	void OnInitialize() override;
	void SetLane(int lane) { m_lane = lane; }
	int GetLane() const { return m_lane; }

	friend class IdleGunState;
	friend class ShootingGunState;
	friend class ReloadingGunState;
	friend class UnloadingGunState;
};

