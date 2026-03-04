#pragma once
#include "Entity.h"
#include "StateMachine.h"

class RugbyScene;



class RugbyMan : public Entity
{
private:
	//reset
	sf::Vector2f m_initialPos;

	int m_team;

	bool m_isStun = false;
	bool m_manualControl = false;


	//La scene a qui on appartien pour ne pas la racup a chaque frame + onCollision
	RugbyScene* m_currentScene;

	StateMachine<RugbyMan> m_stateMachine;

public:

	//Les states de notre stateMachine
	enum class State
	{
		Searching,
		Attacking,
		AttackingWithBall,
		Defending,
		Passing,
		Stun,
		Dribling,

		Count,
	};

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* _RugbyMan) override;

	void Init(int _team, int _lane);
	void Reset();


	//getter
	RugbyScene* GetMyScene() const { return m_currentScene; }
	int GetTeam() const { return m_team; }
	bool RmIsStun() const { return m_isStun; }
	bool isManuel() { return m_manualControl; }
	bool HasBall() const;


	//setter
	void Stun(bool _tralse) { m_isStun = _tralse; }
	void ForceState(int _newState);
	void ManualControl(bool _state);


private:
	void CorrectDir();

private:
	//Le rugbyMan est un animal super sociable, il a plein d'amis
	friend class DefendingState;
	friend class AttackingState;
	friend class PassingState;
	friend class DriblingState;
	friend class SearchingState;

};

