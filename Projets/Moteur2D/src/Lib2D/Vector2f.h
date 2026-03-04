#pragma once

class Vector2f
{
protected:
	float m_x;
	float m_y;

public:
	Vector2f(float PosX, float PosY) : m_x(PosX), m_y(PosY) {}
	void Set(float PosX, float PosY);
	Vector2f& Normalize();
	Vector2f GetVector() const { return { m_x,m_y }; }

	float GetX() const { return m_x; }
	float GetY() const { return m_y; }
};

