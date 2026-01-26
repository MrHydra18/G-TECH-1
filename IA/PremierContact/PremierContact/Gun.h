#pragma once
#include"Timer.h"
#include<iostream>


class Gun
{
public:

	enum class State
	{
		Idle,
		Shooting,
		Reloading
	};

private:

	int m_Bullets;
	int m_MaxBullets;
	int Delay;
	float m_StartTimer = 0.0f;
	State m_CurrentState = State::Idle;
	int m_Transitions[3][3] =
	{
		//Idle   Shoting   Reloading
		{ 0,		1,		  1}, //Idle
		{ 1,		0,		  0}, //Shooting
		{ 1,		0,		  0}, //Reloading
	};

public:

	Gun(int Bulllets, int MaxBullets, int delay) : m_Bullets(Bulllets), m_MaxBullets(MaxBullets), Delay(delay) {}

	void Update(float DeltaTime);
	bool Shoot();
	bool Reload();
	bool CanTransitionTo(State newState);
	bool SetState(State newState);
};

