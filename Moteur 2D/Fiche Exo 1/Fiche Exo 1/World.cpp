#include "World.h"

std::vector<Entity> things;


void World::Init()
{
	things.push_back(StaticObject({ 32, 100 }));
	things.push_back(BreakableObject({ 50, 50 }, 1, 15));
	things.push_back(Mob({ 100, 100 }, 20, 20, { 12, 15 }));
	things.push_back(Player({ 200, 200 }, 10, 10, { 10, 10 }));
}