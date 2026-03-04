#include "RugbyMan.h"

//moteur
#include "Debug.h"
#include "Utils.h"

//state machine
#include "RmStates.h"
#include "RmConditions.h"

//element cool
#include "RugbyScene.h"
#include "Ball.h"

void RugbyMan::OnInitialize()
{
	//initialisation des state
	{


		//Searching
		{
			m_stateMachine.AddState(new SearchingState());

			//->Attacking (prevision)
			Transition<RugbyMan>* pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::Attacking);
			pAuto->AddCondition(new TeamWillHaveBall(true));
			pAuto->AddCondition(new IWillHaveBall(false));

			//->Attacking
			pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::Attacking);
			pAuto->AddCondition(new TeamHasBall(true));
			pAuto->AddCondition(new HaveBall(false));


			//->AttackingWithBall (prevision)
			pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::AttackingWithBall);
			pAuto->AddCondition(new TeamWillHaveBall(true));
			pAuto->AddCondition(new IWillHaveBall(true));

			//->AttackingWithBall
			pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::AttackingWithBall);
			pAuto->AddCondition(new TeamHasBall(true));
			pAuto->AddCondition(new HaveBall(true));

			//->Defending (prevision)
			pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::Defending);
			pAuto->AddCondition(new OtherTeamWillHaveBall(true));

			//->Defending
			pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::Defending);
			pAuto->AddCondition(new OtherTeamHasBall(true));

			//->Stun
			pAuto = m_stateMachine.AddTransition((int)State::Searching, (int)State::Stun);
			pAuto->AddCondition(new IsStun(true));
		}

		//Attacking
		{
			m_stateMachine.AddState(new AttackingState());

			//->Defending
			Transition<RugbyMan>* pAuto = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Defending);
			pAuto->AddCondition(new OtherTeamHasBall(true));


			//->Stun
			pAuto = m_stateMachine.AddTransition((int)State::Attacking, (int)State::Stun);
			pAuto->AddCondition(new IsStun(true));

			//->AttackWitBall (prevision)
			pAuto = m_stateMachine.AddTransition((int)State::Attacking, (int)State::AttackingWithBall);
			pAuto->AddCondition(new IWillHaveBall(true));


			//->AttackWitBall 
			pAuto = m_stateMachine.AddTransition((int)State::Attacking, (int)State::AttackingWithBall);
			pAuto->AddCondition(new HaveBall(true));

		}



		//AttackingWithBall
		{
			m_stateMachine.AddState(new AttackingWithBallState());

			//->Passing
			Transition<RugbyMan>* pAuto = m_stateMachine.AddTransition((int)State::AttackingWithBall, (int)State::Passing);
			pAuto->AddCondition(new TeamateBehind(true));
			pAuto->AddCondition(new EnemyInFrontOfMe(true));
			pAuto->AddCondition(new IsManuel(false));
			pAuto->AddCondition(new IsBorderField(false));


			//->Stun
			pAuto = m_stateMachine.AddTransition((int)State::AttackingWithBall, (int)State::Stun);
			pAuto->AddCondition(new IsStun(true));

			//->Defending
			pAuto = m_stateMachine.AddTransition((int)State::AttackingWithBall, (int)State::Defending);
			pAuto->AddCondition(new OtherTeamHasBall(true));

			//->Attacking 
			pAuto = m_stateMachine.AddTransition((int)State::AttackingWithBall, (int)State::Attacking);
			pAuto->AddCondition(new HaveBall(false));
			pAuto->AddCondition(new TeamHasBall(true));

		}

		//Defensing
		{
			m_stateMachine.AddState(new DefendingState());



			//->Attacking 
			Transition<RugbyMan>* pAuto = m_stateMachine.AddTransition((int)State::Defending, (int)State::Attacking);
			pAuto->AddCondition(new TeamHasBall(true));
			pAuto->AddCondition(new HaveBall(false));


			//->AttackingWithBall 
			pAuto = m_stateMachine.AddTransition((int)State::Defending, (int)State::AttackingWithBall);
			pAuto->AddCondition(new TeamHasBall(true));
			pAuto->AddCondition(new HaveBall(true));




			//->Attacking (prevision)
			pAuto = m_stateMachine.AddTransition((int)State::Defending, (int)State::Attacking);
			pAuto->AddCondition(new TeamWillHaveBall(true));
			pAuto->AddCondition(new IWillHaveBall(false));


			//->AttackingWithBall (prevision)
			pAuto = m_stateMachine.AddTransition((int)State::Defending, (int)State::AttackingWithBall);
			pAuto->AddCondition(new TeamWillHaveBall(true));
			pAuto->AddCondition(new IWillHaveBall(true));


			//->Stun
			pAuto = m_stateMachine.AddTransition((int)State::Defending, (int)State::Stun);
			pAuto->AddCondition(new IsStun(true));
		}

		//passing
		{
			m_stateMachine.AddState(new PassingState());

			Transition<RugbyMan>* pAuto = m_stateMachine.AddTransition((int)State::Passing, (int)State::Attacking);
			//On ne fait QU'UNE passe, donc des qu'on rentre dans le state, on en sort, pas de condition 
			//on passe a attacking par ce qu'on est sense faire la passe a son pote
		}

		//Stun
		{
			m_stateMachine.AddState(new StunState());

			//->Searching
			Transition<RugbyMan>* pAuto = m_stateMachine.AddTransition((int)State::Stun, (int)State::Searching);
			pAuto->AddCondition(new IsStun(false));
		}
	}


	//On set le StateInitiale au state 0 (Searching)
	m_stateMachine.TryTransitionTo(this, 0);

	//On recupere notre scene
	m_currentScene = GetScene<RugbyScene>();
}

void RugbyMan::OnUpdate()
{

	m_stateMachine.Update(this, GetDeltaTime());


	//debug de la State actuel (le numeros au millieu)
	if (m_currentScene->DrawingDebug()) {
		sf::Vector2f pos = GetPosition();
		Debug::DrawText(pos.x - 5, pos.y - 12, std::to_string(m_stateMachine.GetState()), sf::Color::Black);
	}


	//pour les debug avancer, affiche les directions
	if (m_currentScene->m_seeAllDebug)
	{
		sf::Vector2f pos = GetPosition();
		sf::Vector2f nextPos = pos + GetDirection() * GetSpeed() * 0.3f;
		Debug::DrawLine(pos.x, pos.y, nextPos.x, nextPos.y, sf::Color::Black);
	}


	//On verifie qu'on ne depasse pas en haut, en bas, a gauche, a droite 
	CorrectDir();
}

void RugbyMan::OnCollision(Entity* _entity)
{
	//Collision avec un RugbyMan
	if (_entity->IsTag((int)RugbyScene::Tag::Rugbyman)) {

		RugbyMan* rugbyMan = static_cast<RugbyMan*>(_entity);
		//Static_cast + IsTag pour un coup moins elever

		if (rugbyMan->GetTeam() == m_team)
			return;

		if (rugbyMan->HasBall() == false)
			return;


		m_currentScene->GetBall()->SetTarget(sf::Vector2f(0, 0));
		m_currentScene->PushBack(this, 350);
	}

	//Collision avec la balle
	else if (_entity->IsTag((int)RugbyScene::Tag::Ball)) {

		Ball* ball = static_cast<Ball*>(_entity);
		//Static_cast + IsTag pour un coup moins elever

		if (ball->GetSoloTime() <= 0.1f)
			return;

		//si on a la balle, ou si on etais le dernier a l'avoir, on arrete
		if (ball->GetLastOwner() == this || ball->GetOwner() == this) {
			return;
		}

		ball->SetTarget(GetPosition());
		ball->SetOwner(this);
	}
}


void RugbyMan::Reset() {
	//Pas besoins de commenter ca... si ?
	SetPosition(m_initialPos.x, m_initialPos.y);
	SetDirection(0, 0);
	m_stateMachine.TryTransitionTo(this, 0);
}

void RugbyMan::ForceState(int _newState)
{
	//pour la passe forcer
	m_stateMachine.TransiteTo(this, _newState);
}

void RugbyMan::ManualControl(bool _state)
{
	//met de la bonne couleur
	m_manualControl = _state;
	if (_state)
		GetShape()->setFillColor(sf::Color(191, 99, 188));
	else
		GetShape()->setFillColor(GetTeam() == 1 ? sf::Color::Green : sf::Color::Red);
}



void RugbyMan::Init(int _team, int _lane)
{
	m_team = _team;
	m_initialPos = GetPosition();
}

//S'assure que le RugbyMan ne sorte pas de l'ecrant
void RugbyMan::CorrectDir()
{

	//data pour la translation
	float dt = GetDeltaTime();
	float speed = GetSpeed();
	float distance = speed * dt;
	sf::Vector2f translation = GetDirection() * distance;

	//les 4 coins du cercle (haha)
	sf::Vector2f nextPosUp = GetPosition(0.5f, 0) + translation;
	sf::Vector2f nextPosDown = GetPosition(0.5f, 1) + translation;
	sf::Vector2f nextPosLeft = GetPosition(0, 0.5f) + translation;
	sf::Vector2f nextPosRight = GetPosition(1, 0.5f) + translation;



	if (nextPosUp.y < 0)
		SetDirection(GetDirection().x, 1);

	if (nextPosLeft.x < 0)
		SetDirection(1, GetDirection().y);

	if (nextPosDown.y > m_currentScene->GetWindowHeight())
		SetDirection(GetDirection().x, -1);

	if (nextPosRight.x > m_currentScene->GetWindowWidth())
		SetDirection(-1, GetDirection().y);
}

//indique si le joueur est l'owner actuel de la balle
bool RugbyMan::HasBall() const
{
	return m_currentScene->GetBall()->GetOwner() == this;
}

