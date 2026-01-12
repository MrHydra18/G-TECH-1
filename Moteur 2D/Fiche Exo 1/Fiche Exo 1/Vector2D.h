#pragma once
#include<cmath>
class Vector2D
{

public:
	float x;
	float y;

	Vector2D(float x, float y) : x(x), y(y) {}
	Vector2D() : x(0), y(0) {}

	float GetPos() { return x, y; }
	void SetPos(Vector2D pos) { x = pos.x; y = pos.y; }

	Vector2D& Normalize();
};

