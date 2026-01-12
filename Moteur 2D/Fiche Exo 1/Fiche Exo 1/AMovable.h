#pragma once
#include"Vector2D.h"
class AMovable
{
protected:
	Vector2D dir;
	float speed;

public:

	AMovable(Vector2D direction) : dir(direction.Normalize()){}

	virtual void SetDirection(Vector2D dir) { dir.SetPos(dir); }
	virtual Vector2D GetDirection() { return dir; }
	virtual void SetSpeed(float s) { speed = s; }
	virtual float GetSpeed() { return speed; }
	virtual void Move() = 0;
};

