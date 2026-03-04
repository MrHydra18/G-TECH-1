#pragma once
#include "Scene.h"

class RugbyMan;
class Ball;

class RugbyScene : public Scene
{
public:
	enum class Tag 
	{
		Rugbyman,
		Ball,

		Count
	};

private:

	//color
	sf::Color m_firstTeamColor;
	sf::Color m_secondTeamColor;
	sf::Color m_ballColor;

	//recup facile des entity
	std::vector<RugbyMan*> m_team1;
	std::vector<RugbyMan*> m_team2;
	Ball* m_ball;

	//les points
	std::pair<int, int> points = { 0, 0 };
	
	//pour le reset
	bool m_haveBall = false;
	bool m_isBallInit = false;

	//timer au depart
	float m_timer = 0;
	int m_timerStart;


	//pour le pause
	float m_lastTimeMultiplicator = 1.f;

	//control manuel
	RugbyMan* m_controlledRugbyMan = nullptr;

	//drag and drops
	Entity* m_dragged = nullptr;

	//pour les lane
	float m_laneHeight;

public:

	//debug
	bool m_showDebug;
	bool m_seeAllDebug = false;
	bool DrawingDebug() { return m_showDebug; }


	void SpawnBall();
	void InitBall();
	void Reset();

	//base de entity
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	//avec plusieur surchage
	RugbyMan* GetCloserRugbyMan(RugbyMan* _player, int _team);
	RugbyMan* GetCloserRugbyMan(sf::Vector2f _center);
	RugbyMan* GetCloserRugbyMan(sf::Vector2f _center, RugbyMan* _exept);
	RugbyMan* GetCloserRugbyManOnAxeY(sf::Vector2f _center, int team);
	
	//pour les passes
	RugbyMan* GetOptimalMate(RugbyMan* _player);

	//permet recuperer les entitées
	std::vector<RugbyMan*> GetRugbyMans();
	std::vector<RugbyMan*> GetRugbyManFromTeam(int _team);
	Ball* GetBall();

	//avec des petit bonus
	std::vector<RugbyMan*> GetRugbyManSortByDistance(sf::Vector2f _center, int team);



	//pour l'attaque
	int GetBetterSide(RugbyMan* _player, int _team);

	//pour les passes
	int GetDefendersInRadius(RugbyMan* player, float radius);

	//pour les lane
	int GetEmptyLane(RugbyMan* player);

	int GetLaneIndex(int y) const;
	int GetLaneCenterY(int laneIndex) const;

	bool IsBallCarrierInMyLane(RugbyMan* player);

	int HowManyPlayerOnLane(int _team, int _lane);




	//Repulse
	void PushBack(RugbyMan* _center, float _intensity);

	//les points
	void AddPoint(int _team);


private:
	void ReadData();




	friend class SearchingState;
};

