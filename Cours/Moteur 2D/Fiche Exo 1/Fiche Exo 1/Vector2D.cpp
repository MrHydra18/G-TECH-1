#include "Vector2D.h"

Vector2D& Vector2D::Normalize()
{
	float mag = std::sqrt(x * x + y * y);
	if (mag > 0)
	{
		x /= mag;
		y /= mag;
	}
	return *this;
}
