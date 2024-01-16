#pragma once

#include <cmath>

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 Normalize()
	{
		float length = std::sqrt(x * x + y * y);
		if (length != 0.0f)
		{
			x /= length;
			y /= length;
		}

		return Vector2(x, y);
	}

	float Magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return { x - other.x, y - other.y };
	}

	Vector2 operator+(const Vector2& other) const
	{
		return { x + other.x, y + other.y };
	}
};
