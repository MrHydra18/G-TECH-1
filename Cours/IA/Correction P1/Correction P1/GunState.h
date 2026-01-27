#pragma once

#include "StateBase.h"

class Gun;

class IdleGunState : public StateBase<Gun>
{
public:
	void Start(Gun* gun) override {};
	void Update(Gun* gun, float dt) override {};
	void End(Gun* gun) override {};
	bool CanTransitionFrom(Gun* gun, int currentState) override;
};

class ShootingGunState : public StateBase<Gun>
{
	float m_duration = 0.5f;
	float m_timer;

public:
	void Start(Gun* gun) override;
	void Update(Gun* gun, float dt) override;
	void End(Gun* gun) override {};
	bool CanTransitionFrom(Gun* gun, int currentState) override;
};

class ReloadingGunState : public StateBase<Gun>
{
	float m_duration = 2.f;
	float m_timer;

public:
	void Start(Gun* gun) override;
	void Update(Gun* gun, float dt) override;
	void End(Gun* gun) override {};
	bool CanTransitionFrom(Gun* gun, int currentState) override;
};

class UnloadingGunState : public StateBase<Gun>
{
	float m_duration = 2.f;
	float m_timer;

public:
	void Start(Gun* gun) override;
	void Update(Gun* gun, float dt) override;
	void End(Gun* gun) override {};
	bool CanTransitionFrom(Gun* gun, int currentState) override;
};
