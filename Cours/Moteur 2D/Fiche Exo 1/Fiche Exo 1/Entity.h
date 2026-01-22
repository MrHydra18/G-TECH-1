#pragma once
#include<iostream>
#include "Vector2D.h"

class Entity
{
protected:
	Vector2D pos;

public:
	Entity(Vector2D position) : pos(position) {}

	virtual ~Entity() {}

	Vector2D GetPos() { return pos; }
	void SetPos(Vector2D position) { pos = position; }
};