#pragma once

#include <vector>
#include "StateBase.h"

template<typename T>
class StateMachine
{
	int m_currentState;
	std::vector<StateBase<T>*> m_states;

public:
	void Add(StateBase<T>* state) 
	{
		m_states.push_back(state);
	}

	void Update(T* type, float dt)
	{
		m_states[(int)m_currentState]->Update(type, dt);
	}

	void TryTransitionTo(T* type, int state)
	{
		if (m_states[state]->CanTransitionFrom(type, m_currentState) == false)
			return;

		m_states[m_currentState]->End(type);

		m_currentState = state;

		m_states[m_currentState]->Start(type);
	}
};

