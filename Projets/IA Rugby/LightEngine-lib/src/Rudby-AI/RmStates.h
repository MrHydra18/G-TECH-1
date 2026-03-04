#pragma once
#include "StateMachine.h"

class RugbyMan;
class Ball;

class SearchingState : public StateBase<RugbyMan> {
public:

	void Start(RugbyMan* type) override {};
	void Update(RugbyMan* type, float dt) override {};
	void End(RugbyMan* type) override {};
};


class DefendingState : public StateBase<RugbyMan>
{
public:

	void Start(RugbyMan* player) override {};
	void Update(RugbyMan* player, float dt) override;
	void End(RugbyMan* player) override {};
};

class AttackingState : public StateBase<RugbyMan>
{
public:

	void Start(RugbyMan* player) override {};
	bool behindBall(Ball* ball, RugbyMan* player);
	void GoToOptimalPos(RugbyMan* player);
	void Update(RugbyMan* player, float dt) override;
	void End(RugbyMan* player) override {};
};

class AttackingWithBallState : public StateBase<RugbyMan>
{
public:

	void Start(RugbyMan* player) override {};
	void Update(RugbyMan* player, float dt) override;
	void End(RugbyMan* player) override {};
};

class PassingState : public StateBase<RugbyMan>
{
public:

	void Start(RugbyMan* player) override;
	void Update(RugbyMan* player, float dt) override {};
	void End(RugbyMan* player) override {};
};

class DriblingState : public StateBase<RugbyMan>
{
public:

	void Start(RugbyMan* player) override {};
	void Update(RugbyMan* player, float dt) override {};
	void End(RugbyMan* player) override {};
};

class StunState : public StateBase<RugbyMan> {
private:
	float m_stunDuration = .3f;
	float m_counter = 0.f;

public:

	void Start(RugbyMan* type) override;
	void Update(RugbyMan* type, float dt) override;
	void End(RugbyMan* type) override;
};