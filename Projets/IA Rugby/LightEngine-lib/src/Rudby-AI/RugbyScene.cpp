#include "RugbyScene.h"

//module externe
#include <random>

	//pour le data read
	#include <fstream>
	#include <sstream>
	#include <string>


//moteur
#include "Debug.h"
#include "Utils.h"

//MyEntity
#include "RugbyMan.h"
#include "Ball.h"


void RugbyScene::ReadData()
{
	m_timerStart = 3;
	m_firstTeamColor = { 0, 255, 0 };
	m_secondTeamColor = { 255, 0, 0 };
	m_ballColor = { 255, 255, 0 };
	m_showDebug = true;

	std::ifstream file("../../../res/GameSettings.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string key;
			iss >> key;

			if (key == "timerStart:") iss >> m_timerStart;
			else if (key == "firstTeamColor:") {
				int r, g, b;
				iss >> r >> g >> b;
				m_firstTeamColor = sf::Color(r, g, b);
			}

			else if (key == "secondTeamColor:") {
				int r, g, b;
				iss >> r >> g >> b;
				m_secondTeamColor = sf::Color(r, g, b);
			}
			else if (key == "ballColor:") {
				int r, g, b;
				iss >> r >> g >> b;
				m_ballColor = sf::Color(r, g, b);
			}
			else if (key == "drawLane:") iss >> m_showDebug;
		}
	}

}

void RugbyScene::OnInitialize()
{
	srand(time(NULL));

	ReadData();

	m_laneHeight = GetWindowHeight() / 5;

	//init des entitées (do not open...plz)
	{
		RugbyMan* rugbyMan;
		//Equipe 1
		rugbyMan = CreateEntity<RugbyMan>(30.f, m_firstTeamColor);
		rugbyMan->SetPosition(100, 100);
		rugbyMan->Init(1, -1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team1.push_back(rugbyMan);

		rugbyMan = CreateEntity<RugbyMan>(30.f, m_firstTeamColor);
		rugbyMan->SetPosition(100, GetWindowHeight() - 100);
		rugbyMan->Init(1, 1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team1.push_back(rugbyMan);

		rugbyMan = CreateEntity<RugbyMan>(30.f, m_firstTeamColor);
		rugbyMan->SetPosition(225, 200);
		rugbyMan->Init(1, -1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team1.push_back(rugbyMan);

		rugbyMan = CreateEntity<RugbyMan>(30.f, m_firstTeamColor);
		rugbyMan->SetPosition(225, GetWindowHeight() - 200);
		rugbyMan->Init(1, 1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team1.push_back(rugbyMan);

		rugbyMan = CreateEntity<RugbyMan>(30, m_firstTeamColor);
		rugbyMan->SetPosition(300, GetWindowHeight() / 2);
		rugbyMan->Init(1, 0);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team1.push_back(rugbyMan);
		//~Equipe 1


		//Equipe 2
		rugbyMan = CreateEntity<RugbyMan>(30.f, m_secondTeamColor);
		rugbyMan->SetPosition(GetWindowWidth() - 100, 100);
		rugbyMan->Init(2, -1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team2.push_back(rugbyMan);

		rugbyMan = CreateEntity<RugbyMan>(30.f, m_secondTeamColor);
		rugbyMan->SetPosition(GetWindowWidth() - 100, GetWindowHeight() - 100);
		rugbyMan->Init(2, 1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team2.push_back(rugbyMan);


		rugbyMan = CreateEntity<RugbyMan>(30.f, m_secondTeamColor);
		rugbyMan->SetPosition(GetWindowWidth() - 225, 200);
		rugbyMan->Init(2, -1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team2.push_back(rugbyMan);


		rugbyMan = CreateEntity<RugbyMan>(30.f, m_secondTeamColor);
		rugbyMan->SetPosition(GetWindowWidth() - 225, GetWindowHeight() - 200);
		rugbyMan->Init(2, 1);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team2.push_back(rugbyMan);


		rugbyMan = CreateEntity<RugbyMan>(30, m_secondTeamColor);
		rugbyMan->SetPosition(GetWindowWidth() - 300, GetWindowHeight() / 2);
		rugbyMan->Init(2, 0);
		rugbyMan->SetRigidBody(true);
		rugbyMan->SetTag((int)Tag::Rugbyman);
		rugbyMan->SetSpeed(300);
		m_team2.push_back(rugbyMan);


		//~Equipe 2


		//Ball
		Ball* ball = CreateEntity<Ball>(15, m_ballColor);
		ball->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
		ball->SetTag((int)Tag::Ball);
		m_ball = ball;
		//~Ball
	}

}

void RugbyScene::Reset()
{
	for (RugbyMan* rm : m_team1) {
		rm->Reset();
	}
	for (RugbyMan* rm : m_team2) {
		rm->Reset();
	}
	m_ball->Reset();

	m_timer = 0.f;
	m_isBallInit = false;


}

int RugbyScene::GetLaneIndex(int y) const
{
	if (y <= m_laneHeight)
		return 0;

	else if (y <= m_laneHeight * 2)
		return 1;

	else if (y <= m_laneHeight * 3)
		return 2;

	else if (y <= m_laneHeight * 4)
		return 3;

	else if (y <= m_laneHeight * 5)
		return 4;

	else
		return 4;
}

int RugbyScene::GetEmptyLane(RugbyMan* player)
{
	std::vector<RugbyMan*> teammates = GetRugbyManFromTeam(player->GetTeam());

	int laneOccupation[5] = { 0, 0, 0, 0, 0 };

	_ASSERT(teammates.size() == 5);
	
	for (RugbyMan* mate : teammates) {

		int mateLane = GetLaneIndex(mate->GetPosition().y);

		_ASSERT(mateLane >= 0);
		_ASSERT(mateLane < 5);

		laneOccupation[mateLane]++;
	}

	int emptyLaneIndex = 0;
	int minOccupation = laneOccupation[emptyLaneIndex];

	for (int i = 1; i < 5; i++) {
		if (laneOccupation[i] < minOccupation) {
			minOccupation = laneOccupation[i];
			emptyLaneIndex = i;
		}
	}

	return emptyLaneIndex;
}

int RugbyScene::GetLaneCenterY(int laneIndex) const
{
	return (int)(m_laneHeight * laneIndex + m_laneHeight / 2);
}

bool RugbyScene::IsBallCarrierInMyLane(RugbyMan* player)
{
	RugbyMan* carrier = GetBall()->GetOwner();


	if (!carrier || carrier == player)
		return false;

	if (carrier->GetTeam() != player->GetTeam())
		return false;

	int playerLane = GetLaneIndex(player->GetPosition().y);
	int carrierLane = GetLaneIndex(carrier->GetPosition().y);

	return playerLane == carrierLane;
}


int RugbyScene::HowManyPlayerOnLane(int _team, int _lane)
{
	std::vector<RugbyMan*> teamates = GetRugbyManFromTeam(_team);
	int count = 0;
	for (RugbyMan* rugbyMan : teamates) {
		if (GetLaneIndex(rugbyMan->GetPosition().y) == _lane) {
			count++;
		}
	}
	return count;
}

void RugbyScene::OnEvent(const sf::Event& event)
{

	//drag
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
		for (RugbyMan* rm : m_team1) {
			if (rm->IsInside(event.mouseButton.x, event.mouseButton.y)) {
				m_dragged = rm;
				break;
			}
		}
		for (RugbyMan* rm : m_team2) {
			if (rm->IsInside(event.mouseButton.x, event.mouseButton.y)) {
				m_dragged = rm;
				break;
			}
		}
		if (m_ball->IsInside(event.mouseButton.x, event.mouseButton.y))
			m_dragged = m_ball;
	}

	//and drop
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && m_dragged != nullptr) {
		m_dragged->SetPosition(event.mouseButton.x, event.mouseButton.y);
		m_dragged = nullptr;
	}

	//active manual control
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && m_controlledRugbyMan == nullptr)
	{
		for (RugbyMan* rm : m_team1) {
			if (rm->IsInside(event.mouseButton.x, event.mouseButton.y)) {
				rm->ManualControl(true);
				m_controlledRugbyMan = rm;
				break;
			}
		}
		for (RugbyMan* rm : m_team2) {
			if (rm->IsInside(event.mouseButton.x, event.mouseButton.y)) {
				rm->ManualControl(true);
				m_controlledRugbyMan = rm;
				break;
			}
		}
	}

	//do with manual control
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && m_controlledRugbyMan)
	{
		m_controlledRugbyMan->GoToPosition(event.mouseButton.x, event.mouseButton.y);
	}


	//tous les event clavier
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code)
		{
		case(sf::Keyboard::Escape):
			if (GetTimeMultiplicator() == 0.f)
				SetTimeMultiplicator(m_lastTimeMultiplicator);
			else 
			{
				m_lastTimeMultiplicator = GetTimeMultiplicator();
				SetTimeMultiplicator(0.f);
			}
			break;

		case(sf::Keyboard::A):
			m_seeAllDebug = !m_seeAllDebug;
			break;

		case(sf::Keyboard::Z):
			if (m_controlledRugbyMan)
			{
				m_controlledRugbyMan->ManualControl(false);
				m_controlledRugbyMan->ResetTarget();
				m_controlledRugbyMan = nullptr;
			}
			break;
		case(sf::Keyboard::R):
			Reset();
			break;

		case(sf::Keyboard::E):
			if (RugbyMan* rugbyMan = GetBall()->GetOwner()) {
				rugbyMan->ForceState((int)RugbyMan::State::Passing);
			}
			break;
		
		}
	}

	if (event.type == sf::Event::MouseWheelScrolled) {
		m_lastTimeMultiplicator = GetTimeMultiplicator() + event.mouseWheelScroll.delta / 10;
		SetTimeMultiplicator(m_lastTimeMultiplicator);
	}

}

void RugbyScene::OnUpdate()
{
	int lane = GetWindowHeight() / 5;

	//ligne des points
	Debug::DrawLine(130, 0, 130, GetWindowHeight(), sf::Color::White);
	Debug::DrawLine(GetWindowWidth() - 130, 0, GetWindowWidth() - 130, GetWindowHeight(), sf::Color::White);

	if (m_showDebug) {
		//lane
		Debug::DrawLine(0, lane, GetWindowWidth(), lane, sf::Color::Black);
		Debug::DrawLine(0, lane * 2, GetWindowWidth(), lane * 2, sf::Color::Black);
		Debug::DrawLine(0, lane * 3, GetWindowWidth(), lane * 3, sf::Color::Black);
		Debug::DrawLine(0, lane * 4, GetWindowWidth(), lane * 4, sf::Color::Black);

		//controlle
		std::string texte = "Stop Time [ESCAPE] ";
		Debug::DrawText(50, 25, texte, sf::Color::Yellow);

		texte = "Actual Time Multiplicator :" + std::to_string(GetTimeMultiplicator());
		Debug::DrawText(50, 50, texte, sf::Color::Yellow);

		texte = "Show Direction [A]: ";
		if (m_seeAllDebug) {
			texte += "True";
		}
		else
			texte += "False";
		Debug::DrawText(50, 75, texte, sf::Color::Yellow);

		texte = "Reset [R] ";
		Debug::DrawText(50, 100, texte, sf::Color::Yellow);

		texte = "Force Pass [E]";
		Debug::DrawText(50, 125, texte, sf::Color::Yellow);


		texte = "Disable Manual Control [Z]";
		Debug::DrawText(50, 150, texte, sf::Color::Yellow);

	}

	//les points
	std::string text = std::to_string(points.first) + "/" + std::to_string(points.second);
	Debug::DrawText(GetWindowWidth() / 2 - 6, 50, text, sf::Color::Black);

	//affichage du timer
	if (m_timer < m_timerStart) {
		m_timer += GetDeltaTime();
		int time = m_timerStart - (int)(m_timer);
		std::string text = std::to_string(time);
		Debug::DrawText(GetWindowWidth() / 2 - 6, GetWindowHeight() / 2 - 13, text, sf::Color::Black);
	}
	else if (!m_haveBall)
		SpawnBall();
	else if (!m_isBallInit)
		InitBall();
}

std::vector<RugbyMan*> RugbyScene::GetRugbyManFromTeam(int _team)
{
	switch (_team) {
	case(1):
		return m_team1;
	case(2):
		return m_team2;
	}
}

Ball* RugbyScene::GetBall()
{
	return m_ball;
}

RugbyMan* RugbyScene::GetCloserRugbyMan(RugbyMan* _player, int _team)
{
	std::vector<RugbyMan*> mates = GetRugbyManFromTeam(_team);
	RugbyMan* closest = nullptr;

	float dist;
	float minDist = INT_MAX;

	for (RugbyMan* rm : mates) {
		if (rm == _player) continue;
		int posX = rm->GetPosition().x;
		int posY = rm->GetPosition().y;
		int mPosX = _player->GetPosition().x;
		int mPosY = _player->GetPosition().y;

		dist = Utils::GetDistance(posX, posY, mPosX, mPosY);

		if (dist < minDist)
		{
			minDist = dist;
			closest = rm;
		}
	}

	return closest;
}

RugbyMan* RugbyScene::GetCloserRugbyMan(sf::Vector2f _center)
{

	std::vector<RugbyMan*> mates = GetRugbyMans();
	RugbyMan* closest = nullptr;

	float dist;
	float minDist = INT_MAX;

	for (RugbyMan* rm : mates) {
		int posX = rm->GetPosition().x;
		int posY = rm->GetPosition().y;
		int mPosX = _center.x;
		int mPosY = _center.y;

		dist = Utils::GetDistance(posX, posY, mPosX, mPosY);

		if (dist < minDist)
		{
			minDist = dist;
			closest = rm;
		}
	}

	return closest;
}

RugbyMan* RugbyScene::GetCloserRugbyMan(sf::Vector2f _center, RugbyMan* _exept)
{
	std::vector<RugbyMan*> mates = GetRugbyMans();
	RugbyMan* closest = mates[0];

	float dist;
	float minDist = 1000000.f;

	for (RugbyMan* rm : mates) {
		if (rm == _exept) continue;
		int posX = rm->GetPosition().x;
		int posY = rm->GetPosition().y;
		int mPosX = _center.x;
		int mPosY = _center.y;

		dist = Utils::GetDistance(posX, posY, mPosX, mPosY);

		if (dist < minDist)
		{
			minDist = dist;
			closest = rm;
		}
	}

	return closest;
}


void RugbyScene::AddPoint(int _team)
{
	switch (_team) {
	case(1):
		points.first++;
		break;
	case(2):
		points.second++;
		break;
	}
}

void RugbyScene::SpawnBall() {

	GetBall()->Init(rand() % 2 + 1);
	m_haveBall = true;
}

void RugbyScene::InitBall() {
	GetBall()->Init(rand() % 2 + 1);
	m_isBallInit = true;
}

int RugbyScene::GetBetterSide(RugbyMan* _player, int _team)
{

	RugbyMan* closerEnemy = GetCloserRugbyMan(_player, _player->GetTeam() == 1 ? 2 : 1);


	sf::Vector2f dir = _player->GetDirection();
	float speed = _player->GetSpeed();
	float deltaTime = GetDeltaTime();


	sf::Vector2f posIfDown = _player->GetPosition() + sf::Vector2f(dir.x, -0.5f) * speed * deltaTime;
	sf::Vector2f posIfUp = _player->GetPosition() + sf::Vector2f(dir.x, 0.5f) * speed * deltaTime;

	float distanceIfDown = Utils::GetDistance(posIfDown.x, posIfDown.y, closerEnemy->GetPosition().x, closerEnemy->GetPosition().y);
	float distanceIfUp = Utils::GetDistance(posIfUp.x, posIfUp.y, closerEnemy->GetPosition().x, closerEnemy->GetPosition().y);



	return distanceIfDown > distanceIfUp ? -1 : 1;
}

RugbyMan* RugbyScene::GetOptimalMate(RugbyMan* _player)
{
	std::vector<RugbyMan*> teamates = GetRugbyManFromTeam(_player->GetTeam());

	teamates.erase(std::remove(teamates.begin(), teamates.end(), _player), teamates.end());


	sf::Vector2f pos = _player->GetPosition();
	int team = _player->GetTeam();

	teamates.erase(std::remove_if(teamates.begin(), teamates.end(), [team, pos](RugbyMan* a) {
		return team == 1 ? a->GetPosition().x > pos.x : a->GetPosition().x < pos.x;
		}), teamates.end());

	if (teamates.empty()) return nullptr;


	int playerLane = GetLaneIndex(_player->GetPosition().y);


	std::vector<int> dangerPoints;

	for (RugbyMan* mate : teamates)
	{

		int mateLane = GetLaneIndex(mate->GetPosition().y);

		int diffLane = abs(mateLane - playerLane);

		dangerPoints.push_back(GetDefendersInRadius(mate, 150) + diffLane);

		if (_player->GetMyScene()->DrawingDebug()) {
			std::string texte = "Distance = " + std::to_string(diffLane) + ", enemy a porter = " + std::to_string(GetDefendersInRadius(mate, 150));
			Debug::DrawText(mate->GetPosition().x, mate->GetPosition().y - 50, texte, sf::Color::White);
		}
	}

	int index = 0;
	int min = dangerPoints[index];

	for (size_t i = 0; i < dangerPoints.size(); i++) {
		if (dangerPoints[i] < dangerPoints[index]) {
			index = i;
		}
	}

	return teamates[index];



}

void RugbyScene::PushBack(RugbyMan* _center, float _intensity)
{
	std::vector<RugbyMan*> enemys = GetRugbyManFromTeam(_center->GetTeam() == 1 ? 2 : 1);


	//on regarde les quel sont dans le cercle de l'impulsion
	sf::Vector2f centerPos = _center->GetPosition();
	enemys.erase(std::remove_if(enemys.begin(), enemys.end(), [centerPos, _intensity](RugbyMan* a) {
		return Utils::GetDistance(centerPos.x, centerPos.y, a->GetPosition().x, a->GetPosition().y) >= _intensity;
		}),
		enemys.end());

	for (RugbyMan* enemy : enemys) {
		sf::Vector2f dir = enemy->GetPosition() - centerPos;
		Utils::Normalize(dir);
		float force = Utils::GetDistance(enemy->GetPosition().x, enemy->GetPosition().y, centerPos.x, centerPos.y);
		force = _intensity - force;
		enemy->Stun(true);
		enemy->SetDirection(dir.x, dir.y, force * 2);
	}

}

std::vector<RugbyMan*> RugbyScene::GetRugbyManSortByDistance(sf::Vector2f _center, int team)
{
	std::vector<RugbyMan*> teamates = GetRugbyManFromTeam(team);

	std::sort(teamates.begin(), teamates.end(), [&_center](RugbyMan* a, RugbyMan* b) {
		float distA = Utils::GetDistance(a->GetPosition().x, a->GetPosition().y, _center.x, _center.y);
		float distB = Utils::GetDistance(b->GetPosition().x, b->GetPosition().y, _center.x, _center.y);
		return distA < distB;
		});

	return teamates;
}

std::vector<RugbyMan*> RugbyScene::GetRugbyMans()
{
	std::vector<RugbyMan*> result;
	for (RugbyMan* rm : m_team1) {
		result.push_back(rm);
	}
	for (RugbyMan* rm : m_team2) {
		result.push_back(rm);
	}

	return result;
}

RugbyMan* RugbyScene::GetCloserRugbyManOnAxeY(sf::Vector2f _center, int team) {

	std::vector<RugbyMan*> enemys = GetRugbyManFromTeam(team);


	RugbyMan* optimal = nullptr;
	float min_dist = INT_MAX;

	for (RugbyMan* rm : enemys) {

		float dist = abs(rm->GetPosition().y - _center.y);

		if (dist < min_dist) {
			min_dist = dist;
			optimal = rm;
		}
	}

	return optimal;

}

int RugbyScene::GetDefendersInRadius(RugbyMan* player, float radius)
{

	RugbyScene* scene = player->GetMyScene();

	std::vector<RugbyMan*> enemies = GetRugbyManFromTeam(player->GetTeam() == 1 ? 2 : 1);

	int dangerPoints = 0;


	sf::Vector2f matePos = player->GetPosition();


	for (RugbyMan* enemi : enemies)
	{
		sf::Vector2f enemiPos = enemi->GetPosition();
		float distance = Utils::GetDistance(matePos.x, matePos.y, enemiPos.x, enemiPos.y);

		if (distance < radius)
			dangerPoints++;
	}

	if (scene->DrawingDebug()) {
		Debug::DrawCircle(matePos.x, matePos.y, radius, sf::Color(225, 158, 255, 15));
	}

	return dangerPoints;
}
