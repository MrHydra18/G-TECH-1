#pragma once
#include "FirstScene.h"
#include "StateBase.h"

class Plant;

class IdlePlantState : public StateBase<Plant>
{
public:
	void Start(Plant* plant) override;
	void Update(Plant* plant, float dt) override {};
	void End(Plant* plant) override {};
	bool CanTransitionFrom(Plant* plant, int currentState) override;
};

class ShootingPlantState : public StateBase<Plant>
{
	float m_duration = 0.5f;
	float m_timer;

public:
	void Start(Plant* plant) override;
	void Update(Plant* plant, float dt) override;
	void End(Plant* plant) override {};
	bool CanTransitionFrom(Plant* plant, int currentState) override;
};

class ReloadingPlantState : public StateBase<Plant>
{
	float m_duration = 2.f;
	float m_timer;

public:
	void Start(Plant* plant) override;
	void Update(Plant* plant, float dt) override;
	void End(Plant* plant) override {};
	bool CanTransitionFrom(Plant* plant, int currentState) override;
};

