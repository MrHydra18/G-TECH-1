#include "Gun.h"
#include<Windows.h>

void Gun::Update(float DeltaTime)
{
	m_StartTimer += DeltaTime;

	switch (m_CurrentState)
	{
	case (State::Idle):
		system("cls");
		std::cout << "State: Idle" << "| Ammo: " << m_Bullets << "/" << m_MaxBullets << "| Progress: " << m_StartTimer << std::endl;
		Sleep(Delay);
		break;

	case (State::Reloading):
		system("cls");
		std::cout << "State: Reloading" << "| Ammo: " << m_Bullets << "/" << m_MaxBullets << "| Progress: " << m_StartTimer << std::endl;
		Sleep(Delay);
		break;

	case (State::Shooting):
		system("cls");
		std::cout << "State: Reloading" << "| Ammo: " << m_Bullets << "/" << m_MaxBullets << "| Progress: " << m_StartTimer << std::endl;
		Sleep(Delay);
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

	m_StartTimer = 0.0f;
	SetState(State::Shooting);

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
	m_StartTimer = 0.0f;
	SetState(State::Reloading);

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

