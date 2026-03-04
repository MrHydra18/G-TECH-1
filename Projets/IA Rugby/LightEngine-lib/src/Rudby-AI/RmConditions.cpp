 #include "RmConditions.h"
#include "RugbyMan.h"
#include "RugbyScene.h"
#include "Ball.h"
#include "Utils.h"


bool TeamHasBall::Test(RugbyMan* mate)
{
    RugbyMan* ballOwner = mate->GetScene<RugbyScene>()->GetBall()->GetOwner();
    if (!ballOwner)
        return !m_assert; //si personne l'a, l'autre l'a pas
    int teamWhoHasBall = ballOwner->GetTeam();
    return (teamWhoHasBall == mate->GetTeam()) == m_assert;
}


bool OtherTeamHasBall::Test(RugbyMan* mate)
{
    RugbyMan* ballOwner = mate->GetScene<RugbyScene>()->GetBall()->GetOwner();
    if (!ballOwner)
        return !m_assert; //si personne l'a, l'autre l'a pas
    int teamWhoHasBall = ballOwner->GetTeam();
    return (teamWhoHasBall != mate->GetTeam()) == m_assert;
}

bool EnemyInFrontOfMe::Test(RugbyMan* player)
{
    int enemyTeam = (player->GetTeam() == 1) ? 2 : 1;
    std::vector<RugbyMan*> enemies = player->GetScene<RugbyScene>()->GetRugbyManFromTeam(enemyTeam);

    sf::Vector2f playerPos = player->GetPosition();
    float dirX = (player->GetTeam() == 1) ? 1.0f : -1.0f;

    // centre du cercle devant le joueur
    float cx = playerPos.x + dirX * 75;
    float cy = playerPos.y;

    for (RugbyMan* enemy : enemies) {
        sf::Vector2f ePos = enemy->GetPosition();
        float dist = Utils::GetDistance(ePos.x, ePos.y, cx, cy);
        if (dist < 75) {
            return true == m_assert;
        }
    }

    return false == m_assert;
}

bool TeamateBehind::Test(RugbyMan* player)
{
    if (player->GetMyScene()->GetOptimalMate(player) != nullptr)
        return true == m_assert;
    return false == m_assert;
}

bool HaveBall::Test(RugbyMan* mate)
{
    return (mate->HasBall()) == m_assert;
}

bool IsStun::Test(RugbyMan* mate)
{
    return mate->RmIsStun() == m_assert;

}

bool IsManuel::Test(RugbyMan* mate)
{
    return mate->isManuel() == m_assert;
}

bool BallIsLoseSince::Test(RugbyMan* mate)
{

    return mate->GetMyScene()->GetBall()->GetSoloTime() > m_time == m_assert;
}

bool TeamWillHaveBall::Test(RugbyMan* mate)
{

    if (RugbyMan* futurOwner = mate->GetMyScene()->GetBall()->GetFuturOwner().first) {

        return futurOwner->GetTeam() == mate->GetTeam() == m_assert;
    }
    return false == m_assert;
}

bool IWillHaveBall::Test(RugbyMan* mate)
{
    if (RugbyMan* futurOwner = mate->GetMyScene()->GetBall()->GetFuturOwner().first) {

        return futurOwner == mate == m_assert;
    }
    return false == m_assert;
}

bool OtherTeamWillHaveBall::Test(RugbyMan* mate)
{
    if (RugbyMan* futurOwner = mate->GetMyScene()->GetBall()->GetFuturOwner().first) {

        return futurOwner->GetTeam() == (mate->GetTeam() == 1 ? 2 : 1) == m_assert;
    }
    return false == m_assert;
}

bool IsBorderField::Test(RugbyMan* mate)
{
    float playerLane = mate->GetMyScene()->GetLaneIndex(mate->GetPosition().y);

    if (playerLane != 0 && playerLane != 4)
        return false == m_assert;

    return true == m_assert;
}
