#pragma once
#include "Entity.h"


class RugbyMan;

class Ball : public Entity
{
private:
	RugbyMan* m_owner = nullptr;
	RugbyMan* m_lastOwner = nullptr;
	std::pair<RugbyMan*, sf::Vector2f> m_futurOwner = { nullptr, {0, 0} };

	float m_timeSolo = 0.f;

public:
	

	void OnUpdate() override;
	
	void Init(int _team);
	void Reset();


	void SetTarget(sf::Vector2f _target);
	void SetOwner(RugbyMan* _owner);


	float GetSoloTime() { return m_timeSolo; }
	RugbyMan* GetLastOwner() { return m_lastOwner; }
	RugbyMan* GetOwner() const { return m_owner; }
	std::pair<RugbyMan*, sf::Vector2f> GetFuturOwner() { return m_futurOwner; }

private:

	void CorrectDir();
	RugbyMan* IsColliding(float _radius, sf::Vector2f _pos);
};

