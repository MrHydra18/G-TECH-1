#include "RmStates.h"

//Moteur
#include "Utils.h"
#include "Debug.h"

//Scene
#include "RugbyScene.h"

//entity
#include "RugbyMan.h"
#include "Ball.h"



void DefendingState::Update(RugbyMan* player, float dt)
{
	if (player->isManuel())
		return;


	RugbyScene* scene = player->GetMyScene();
	Ball* ball = scene->GetBall();

	int playerline = scene->GetLaneIndex(player->GetPosition().y);
	int ballline = scene->GetLaneIndex(ball->GetPosition().y);

	int linedif = abs(ballline - playerline);

	int targetX;
	int targetY = scene->GetLaneCenterY(playerline);

	int maxPlayeronLane;

	//on fait la moyenne des position X
	std::vector<RugbyMan*> teamates = scene->GetRugbyManFromTeam(player->GetTeam());

	int coef = teamates.size();
	int sum = 0;


	for (RugbyMan* rm : teamates) {
		sum += rm->GetPosition().x;
	}




	//si jamais on est proche de la balle
	switch (linedif) {
	case(0):
		targetY = ball->GetPosition().y;
		maxPlayeronLane = 3;
		targetX = ball->GetPosition().x;
		break;
	case(1):
		targetY = (targetY + ball->GetPosition().y + ball->GetPosition().y) / 3;
		maxPlayeronLane = 2;
		targetX = sum / coef;
		break;
	default:
		maxPlayeronLane = 1;
		targetX = sum / coef;
		break;
	}

		

	if (scene->HowManyPlayerOnLane(player->GetTeam(), playerline) >= maxPlayeronLane) {
		targetY = scene->GetLaneCenterY(scene->GetEmptyLane(player));
	}

	//on se deplace vers la balle
	targetX += (ball->GetPosition().x < targetX ? -1 : 1) * 100 * linedif;


	if (scene->DrawingDebug())
		Debug::DrawText(player->GetPosition().x, player->GetPosition().y + 50, std::to_string(linedif), sf::Color::Red);


	sf::Vector2f dir = sf::Vector2f(targetX, targetY) - player->GetPosition();

	Utils::Normalize(dir);
	player->SetDirection(dir);

}

bool AttackingState::behindBall(Ball* ball, RugbyMan* player)
{

	switch (player->GetTeam()) {

	case(1):
		return player->GetPosition().x < ball->GetPosition().x;
	case(2):
		return player->GetPosition().x > ball->GetPosition().x;

	}
}

void AttackingState::GoToOptimalPos(RugbyMan* player)
{
	RugbyScene* scene = player->GetMyScene();

	Ball* ball = scene->GetBall();

	float dirX = (player->GetTeam() == 1) ? 1.0f : -1.0f;


	int targetX = dirX;
	int targetY;

	//savoir selon la team vers ou tu vas
	if (behindBall(ball, player) == false)
		targetX = -dirX;

	if (scene->DrawingDebug()) {
		if (behindBall(ball, player))
			Debug::DrawText(player->GetPosition().x, player->GetPosition().y, "on est deriere" + std::to_string(targetX), sf::Color::White);
		else
			Debug::DrawText(player->GetPosition().x, player->GetPosition().y, "on est devant" + std::to_string(targetX), sf::Color::White);
	}

	int currentLane = scene->GetLaneIndex(player->GetPosition().y);

	if (scene->HowManyPlayerOnLane(player->GetTeam(), currentLane) >= 2)
	{
		int targetLane = scene->GetEmptyLane(player);
		targetY = scene->GetLaneCenterY(targetLane);

	}
	else
		targetY = scene->GetLaneCenterY(currentLane);



	sf::Vector2f dir = sf::Vector2f(targetX, targetY) - player->GetPosition();

	Utils::Normalize(dir);
	player->SetDirection(targetX, dir.y);

}

void AttackingState::Update(RugbyMan* player, float dt)
{

	if (player->m_manualControl)
		return;

	GoToOptimalPos(player);

}

void PassingState::Start(RugbyMan* player)
{
	RugbyScene* scene = player->GetMyScene();
	RugbyMan* mate = scene->GetOptimalMate(player);
	if (mate == nullptr)
		return;
	RugbyMan* OptiMate = mate;

	scene->GetBall()->SetTarget(OptiMate->GetPosition());

}

void StunState::Start(RugbyMan* type)
{
	m_counter = 0.f;
	type->GetShape()->setFillColor(sf::Color::Magenta);
}

void StunState::Update(RugbyMan* type, float dt)
{
	m_counter += dt;
	if (m_counter > m_stunDuration)
		type->Stun(false);
}

void StunState::End(RugbyMan* type)
{
	type->GetShape()->setFillColor(type->GetTeam() == 1 ? sf::Color::Green : sf::Color::Red);
	if (type->isManuel()) {
		type->GetShape()->setFillColor(sf::Color(191, 99, 188));
	}
	type->SetSpeed(300);
}

void AttackingWithBallState::Update(RugbyMan* player, float dt)
{

	if (player->isManuel())
		return;

	if (player->HasBall() == false) {

		sf::Vector2f target = player->GetMyScene()->GetBall()->GetFuturOwner().second;
		sf::Vector2f dir = target - player->GetPosition();

		Utils::Normalize(dir);
		player->SetDirection(dir);
		return;
	}

	RugbyScene* scene = player->GetMyScene();

	int dirX = (player->GetTeam() == 1) ? 1 : -1;

	int side = scene->GetBetterSide(player, player->GetTeam());
	player->SetDirection(dirX, 0.5f * side);
	player->SetSpeed(300);


	//Debug si option on
	if (scene->DrawingDebug()) {

		sf::Vector2f pos = player->GetPosition();



		RugbyMan* teamate = scene->GetOptimalMate(player);
		Debug::DrawLine(pos.x, pos.y, teamate->GetPosition().x, teamate->GetPosition().y, sf::Color::White);





		// Debug cercle devant le joueur
		float cx = pos.x + dirX * 75;
		float cy = pos.y;
		sf::Color MyColor(0, 255, 255, 75);
		Debug::DrawCircle(cx, cy, 75, MyColor);
	}
}