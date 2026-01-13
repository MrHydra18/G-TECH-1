#include "World.h"


void World::Init()
{
    things.push_back(new StaticObject(Vector2D{ 32, 100 }));
    things.push_back(new BreakableObject(Vector2D{ 50, 50 }, 1, 15));
    things.push_back(new Mob(Vector2D{ 100, 100 }, 20, 20, Vector2D{ 12, 15 }));
    things.push_back(new Player(Vector2D{ 200, 200 }, 10, 10, Vector2D{ 10, 10 }));
}

void World::Step()
{
    for (auto& thing : things)
    {
        if (Mob* mob = dynamic_cast<Mob*>(thing))
        {
            mob->Move();
            std::cout << "Mob" << std::endl;
        }
        else if (Player* player = dynamic_cast<Player*>(thing))
        {
            player->Move();
            std::cout << "Player" << std::endl;
        }
        else if (BreakableObject* breakable = dynamic_cast<BreakableObject*>(thing))
        {
            std::cout << "BreakableObject" << std::endl;
        }
        else if (StaticObject* static_obj = dynamic_cast<StaticObject*>(thing))
        {
            std::cout << "StaticObject" << std::endl;
        }
    }
}