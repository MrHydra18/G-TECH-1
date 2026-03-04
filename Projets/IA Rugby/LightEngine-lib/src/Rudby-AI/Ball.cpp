#include "Ball.h"
#include "RugbyScene.h"
#include "RugbyMan.h"
#include "Utils.h"

void Ball::Init(int _team)
{

	std::vector<RugbyMan*> rugbyMans = GetScene<RugbyScene>()->GetRugbyManFromTeam(_team);

	int playerIndex = rand() % rugbyMans.size();

	SetTarget(rugbyMans[playerIndex]->GetPosition());
}

void Ball::OnUpdate()
{

	if (m_owner == nullptr)
		m_timeSolo += GetDeltaTime();

	if (m_timeSolo >= 1) {
		m_lastOwner = nullptr;
	}

	CorrectDir();

	if (m_owner) {
		//on se colle a l'owner
		SetDirection(0, 0);
		SetPosition(m_owner->GetPosition().x, m_owner->GetPosition().y);


		//si on marque
		if (GetPosition().x > GetScene()->GetWindowWidth() - 130 && m_owner->GetTeam() == 1) {
			GetScene<RugbyScene>()->AddPoint(1);
			GetScene<RugbyScene>()->Reset();
		}

		else if (GetPosition().x < 130 && m_owner->GetTeam() == 2)
		{
			GetScene<RugbyScene>()->AddPoint(2);
			GetScene<RugbyScene>()->Reset();
		}
	}
}

void Ball::SetTarget(sf::Vector2f _target)
{
	m_lastOwner = m_owner;
	m_owner = nullptr;
	m_futurOwner = { nullptr, sf::Vector2f()};

	//data necessaire a la simulation (pas fixe pour la simulation)
	float deltaTime = 1.0f / 60.0f;
	float speed = 450;
	sf::Vector2f dir = _target - GetPosition();
	Utils::Normalize(dir);
	sf::Vector2f nextPos = GetPosition() + dir * speed * deltaTime;
	float radius = GetRadius() + 300 * deltaTime;

	while (m_futurOwner.first == nullptr) {
		//regarder la pos d'apres

		//si sa touche, fin
		if (RugbyMan* rm = IsColliding(radius, nextPos)) {
			if (rm == m_lastOwner) continue;
			m_futurOwner = { rm, nextPos };
			break;
		}

		//sinon, on verifie si on depasseras au prochain tours & on corrige:
		{
			sf::Vector2f translation = dir * speed * deltaTime;
			float r = GetRadius();

			if (nextPos.y + r + translation.y >= GetScene()->GetWindowHeight())
				dir.y = -1;

			if (nextPos.y - r + translation.y <= 0)
				dir.y = -1;

			if (nextPos.x - r + translation.x <= 0)
				dir.x = -1;

			if (nextPos.x + r + translation.x >= GetScene()->GetWindowWidth())
				dir.x = -1;
		}

		//puis on incremente nos valeurs :

		radius += 300 * deltaTime;
		nextPos += dir * speed * deltaTime;
	}

	if (_target != sf::Vector2f(0, 0)) {
		sf::Vector2f dir = _target - GetPosition();
		Utils::Normalize(dir);
		SetDirection(dir.x, dir.y, 450);
	}
}

void Ball::SetOwner(RugbyMan* _owner)
{
	m_futurOwner = { nullptr, { 0, 0 } };
	m_owner = _owner; 
	m_timeSolo = 0.f; 
}


void Ball::Reset() {
	m_owner = nullptr;
	m_lastOwner = nullptr;
	m_futurOwner = { nullptr, sf::Vector2f() };
	SetPosition(GetScene()->GetWindowWidth() / 2, GetScene()->GetWindowHeight() / 2);
	SetDirection(0, 0);
}

void Ball::CorrectDir()
{
	float dt = GetDeltaTime();
	float speed = GetSpeed();
	sf::Vector2f dir = GetDirection();
	sf::Vector2f translation = dir * speed * dt;
	sf::Vector2f nextPosUp = GetPosition(0.5, 0) + translation;
	sf::Vector2f nextPosDown = GetPosition(0.5, 1) + translation;
	sf::Vector2f nextPosLeft = GetPosition(0, 0.5) + translation;
	sf::Vector2f nextPosRight = GetPosition(1, 0.5) + translation;


	if (nextPosDown.y >= GetScene()->GetWindowHeight()) {
		SetDirection(GetDirection().x, -GetDirection().y);
	}
	if (nextPosUp.y <= 0) {
		SetDirection(GetDirection().x, -GetDirection().y);
	}
	if (nextPosLeft.x <= 0) {
		SetDirection(-GetDirection().x, GetDirection().y);
	}
	if (nextPosRight.x >= GetScene()->GetWindowWidth()) {
		SetDirection(-GetDirection().x, GetDirection().y);
	}

}

RugbyMan* Ball::IsColliding(float _radius, sf::Vector2f _pos)
{
	RugbyMan* closer = GetScene<RugbyScene>()->GetCloserRugbyMan(_pos, m_lastOwner);


	if (Utils::GetDistance(closer->GetPosition().x, closer->GetPosition().y, _pos.x, _pos.y) <= _radius) {
		return closer;
	}

	return nullptr;
}
