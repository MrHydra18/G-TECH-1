#include "Transformable.h"
#include<iostream>
void Transformable::SetPosition(Vector2f NewPos)
{
	Position.Set(NewPos.GetX(), NewPos.GetY());
}

float Transformable::GetDistance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrt(dx * dx + dy * dy);
}

bool Transformable::Move(float MovX, float MovY, float Speed)
{
	Position.Set(Position.GetX() + MovX * Speed, Position.GetY());
	Position.Set(Position.GetX(), Position.GetY() + MovY * Speed);
	if (CollideAndBounce())
		return true;
	return false;
}

void Transformable::Move(Vector2f* Movement, float Speed)
{
	Move(Movement->GetX(), Movement->GetY(), Speed);
}

bool Transformable::CollideAndBounce()
{
	// Collision droite
	if (Position.GetX() + m_Width >= 965)
	{
		Position.Set(965 - m_Width, Position.GetY());
		SetDirection(-m_DirectionX, m_DirectionY);
		return true;
	}

	// Collision gauche
	if (Position.GetX() <= 5)
	{
		Position.Set(5, Position.GetY());
		SetDirection(-m_DirectionX, m_DirectionY);
		return true;
	}

	// Collision bas
	if (Position.GetY() >= 480 - m_Height)
	{
		Position.Set(Position.GetX(), 480 - m_Height);
		SetDirection(m_DirectionX, -m_DirectionY);
		return true;
	}

	// Collision haut
	if (Position.GetY() <= 0)
	{
		Position.Set(Position.GetX(), 0);
		SetDirection(m_DirectionX, -m_DirectionY);
		return true;
	}
	return false;
}

bool Transformable::CollideBall(const Transformable* other)
{

	Vector2f center1 = GetPosition(0.5f, 0.5f);
	Vector2f center2 = other->GetPosition(0.5f, 0.5f);

	float distance = GetDistance(center1.GetX(), center1.GetY(),
		center2.GetX(), center2.GetY());

	float radiusDist = GetRadius() + other->GetRadius();
	std::cout << distance;

	if (distance <= radiusDist)
		return true;

	return false;
}