#pragma once

template<typename T>
class StateBase
{
public:
	virtual void Start(T* plant) = 0;
	virtual void Update(T* plant, float dt) = 0;
	virtual void End(T* plant) = 0;
	virtual bool CanTransitionFrom(T* plant, int currentState) = 0;
};
