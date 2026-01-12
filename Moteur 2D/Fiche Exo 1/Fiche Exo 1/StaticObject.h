#pragma once
#include "Entity.h"

class StaticObject : public Entity
{

public:

	StaticObject(Vector2D pos) : Entity(pos) {
		std::cout << "Static Object just created at x = " << GetPos().x << " and y = " << GetPos().y << std::endl;}
};

