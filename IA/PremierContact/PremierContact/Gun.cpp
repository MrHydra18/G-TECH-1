#include "Gun.h"
#include"Timer.h"
#include<Windows.h>

void Gun::Update(float DeltaTime)
{
	m_StartTimer += DeltaTime;
	std::cout << DeltaTime << std::endl;
	if (m_StartTimer >= m_Delay)
	{
		m_CurrentState = State::Idle;
		m_StartTimer = 0;
	}

	switch (m_CurrentState)
	{
	case (State::Idle):
		std::cout << "State: Idle" << "| Ammo: " << m_Bullets << "/" << m_MaxBullets << "| Progress: " << m_StartTimer << std::endl;
		Sleep(m_Delay);
		break;

	case (State::Reloading):
		std::cout << "State: Reloading" << "| Ammo: " << m_Bullets << "/" << m_MaxBullets << "| Progress: " << m_StartTimer << std::endl;
		Sleep(m_Delay);
		break;

	case (State::Shooting):
		std::cout << "State: Shooting" << "| Ammo: " << m_Bullets << "/" << m_MaxBullets << "| Progress: " << m_StartTimer << std::endl;
		Sleep(m_Delay);
		break;
	}
}

bool Gun::Shoot()
{
	if (m_Bullets <= 0)
	{
		std::cout << "Tu as plus de balles\n";
		return false;
	}

	m_Bullets--;
	std::cout << "Bang! Ammo : " << m_Bullets << "/" << m_MaxBullets << std::endl;

	SetState(State::Idle);

	return true;
}

bool Gun::Reload()
{
	if (m_Bullets == m_MaxBullets)
	{
		std::cout << "Chargeur plein.\n";
		return false;
	}

	std::cout << "Reloading...\n";
	m_Bullets = m_MaxBullets;
	SetState(State::Idle);

	return true;
}


bool Gun::CanTransitionTo(State newState)
{
	int currentStateIndex = static_cast<int>(m_CurrentState);
	int newStateIndex = static_cast<int>(newState);
	if (m_Transitions[currentStateIndex][newStateIndex] == 0)
	{
		return false;
	}

	return true;
}

bool Gun::SetState(State newState)
{
	int currentStateIndex = static_cast<int>(m_CurrentState);
	int newStateIndex = static_cast<int>(newState);
	if (m_Transitions[currentStateIndex][newStateIndex] == 0)
		return false;

	m_CurrentState = newState;

	return true;
}

