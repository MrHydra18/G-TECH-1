#pragma once
#include "Vector2f.h"
#include <cmath>

class PongPlayer;

class Transformable 
{
protected:
	Vector2f Position;
	int m_Width;
	int m_Height;
	float m_DirectionX = 0;
	float m_DirectionY = 0;

public:
	Transformable(float PosX, float PosY) : Position(PosX, PosY){}
	void SetPosition(Vector2f NewPos);
	Vector2f GetPosition() const { return Position; }

	Vector2f GetPosition(float anchorX, float anchorY) const {
		return Vector2f(Position.GetX() + m_Width * anchorX, Position.GetY() + m_Height * anchorY); }

	void SetDirection(float dx, float dy) { m_DirectionX = dx; m_DirectionY = dy; }

	float GetDirectionX() const { return m_DirectionX; }
	float GetDirectionY() const { return m_DirectionY; }


	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }


	float GetRadius() const { return m_Width / 2.0f; }
	static float GetDistance(float x1, float y1, float x2, float y2);

	bool Move(float MovX, float MovY, float Speed);
	void Move(Vector2f* Movement, float Speed);

	bool CollideAndBounce();
	bool CollideBall(const Transformable* other);

};

