#pragma once
#include "Entity.h"
#include"StaticObject.h"
#include"BreakableObject.h"
#include"Mob.h"
#include"Player.h"
#include<vector>

class World
{
	std::vector<Entity*> things;

public:


	void Init();
	void Step();
};

