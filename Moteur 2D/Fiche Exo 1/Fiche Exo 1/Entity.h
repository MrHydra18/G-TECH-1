#pragma once
#include<iostream>
#include "Vector2D.h"

class Entity
{
protected:
	Vector2D pos;

public:	
	Entity(Vector2D position) : pos(position) {}

	Vector2D GetPos() { return pos; };
	void SetPos(Vector2D pos) { pos.x = GetPos().x, pos.y = GetPos().y; };
};

