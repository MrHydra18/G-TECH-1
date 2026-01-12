#include "World.h"

void World::Init()
{
    things.push_back(std::make_unique<StaticObject>(Vector2D{ 32, 100 }));
    things.push_back(std::make_unique<BreakableObject>(Vector2D{ 50, 50 }, 1, 15));
    things.push_back(std::make_unique<Mob>(Vector2D{ 100, 100 }, 20, 20, Vector2D{ 12, 15 }));
    things.push_back(std::make_unique<Player>(Vector2D{ 200, 200 }, 10, 10, Vector2D{ 10, 10 }));
}

void World::Step()
{
    for (auto& thing : things)
    {
        if (Mob* mob = dynamic_cast<Mob*>(thing.get()))
        {
            mob->Move();
            std::cout << "C'est un Mob !" << std::endl;
        }
        else if (Player* player = dynamic_cast<Player*>(thing.get()))
        {
            player->Move();
            std::cout << "C'est un Player !" << std::endl;
        }
        else if (BreakableObject* breakable = dynamic_cast<BreakableObject*>(thing.get()))
        {
            std::cout << "C'est un objet cassable !" << std::endl;
        }
        else if (StaticObject* static_obj = dynamic_cast<StaticObject*>(thing.get()))
        {
            std::cout << "C'est un objet statique !" << std::endl;
        }
    }
}