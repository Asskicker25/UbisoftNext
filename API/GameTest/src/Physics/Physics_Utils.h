#pragma once
#include "../../App/app.h"
#include <string>

class CPhysicsShape;
class CGameObject;

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

struct SLine
{
	SLine()
	{
		mStartPoint = Vector2(0, 0);
		mEndPoint = Vector2(0, 0);
	}
	SLine(Vector2 startPoint, Vector2 endPoint)
	{
		mStartPoint = startPoint;
		mEndPoint = endPoint;
	}

	Vector2 mStartPoint;
	Vector2 mEndPoint;
};

extern bool CheckCollision(CPhysicsShape* a, CPhysicsShape* b);
extern bool CheckCollisionWithTag(CPhysicsShape* a,const std::string& tag, std::vector<CGameObject*>& collidedObjects);

extern bool CircleVsCircle(SCircle& a, SCircle& b);
extern bool BoxVsBox(SBox& a, SBox& b);
extern bool LineVsLine(SLine& a, SLine& b);

extern bool CircleVsBox(SCircle& circle, SBox& box);
extern bool CircleVsLine(SCircle& circle, SLine& line);
extern bool BoxVsLine(SBox& box, SLine& line);

