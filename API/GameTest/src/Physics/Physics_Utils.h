#pragma once
#include "../../App/app.h"
#include "CPhysicsShape.h"

struct SCircle
{
	SCircle() 
	{ 
		mCenter = Vector2(0, 0);
		mRadius = 0;
	};

	Vector2 mCenter;
	float mRadius;
};

struct SBox
{
	SBox()
	{
		mMinPoint = Vector2(0, 0);
		mMaxPoint = Vector2(0, 0);
	};

	Vector2 mMinPoint;  
	Vector2 mMaxPoint;
};

extern bool CheckCollision(CPhysicsShape& a, CPhysicsShape& b);

extern bool CircleVsCircle(SCircle& a, SCircle& b);
extern bool BoxVsBox(SBox& a, SBox& b);
