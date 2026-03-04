#include <iostream>
#include "Vector2f.h"

void Vector2f::Set(float PosX, float PosY)
{
	m_x = PosX;
	m_y = PosY;
}

Vector2f& Vector2f::Normalize()
{ 
	float mag = std::sqrt(m_x * m_x + m_y * m_y);
	if (mag > 0)
	{
		m_x /= mag;
		m_y /= mag;
	}
	return *this;
}
