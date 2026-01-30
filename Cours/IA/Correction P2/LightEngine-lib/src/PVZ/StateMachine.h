#pragma once
#include <vector>
#include "StateBase.h"

template<typename T>
class StateMachine {
private:

	int m_currentState = 0;
	std::vector<StateBase<T>*> m_states;

public:
	void AddState(StateBase<T>* newState)
	{
		m_states.push_back(newState);
	}

	void Update(T* type, float dt)
	{
		m_states[m_currentState]->Update(type, dt);
	}

	void TryTransitionTo(T* type,int nextState)
	{
		if (m_states[(int)nextState]->CanTransitionFrom(type, (int)m_currentState) == false)
			return;

		m_states[(int)m_currentState]->End(type);

		m_currentState = nextState;

		m_states[(int)m_currentState]->Start(type);
	}

	int GetState() const 
	{
		return m_currentState;
	}
};