#pragma once

template<typename T>
class StateBase
{
public:
	virtual void Start(T* gun) = 0;
	virtual void Update(T* gun, float dt) = 0;
	virtual void End(T* gun) = 0;
	virtual bool CanTransitionFrom(T* gun, int currentState) = 0;
};
