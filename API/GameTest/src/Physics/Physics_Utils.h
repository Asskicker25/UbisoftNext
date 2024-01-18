#pragma once
#include "../../App/app.h"
#include <string>

class CPhysicsShape;
class CGameObject;

// Structure representing a circle in 2D space.
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

// Structure representing an axis-aligned box in 2D space.
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

// Structure representing a line segment in 2D space.
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

// Function declarations for collision detection and raycasting functions.
extern bool CheckCollision(CPhysicsShape* self, CPhysicsShape* other);
extern bool CheckCollisionWithTag(CPhysicsShape* self,const std::string& tag, std::vector<CGameObject*>& collidedObjects);
extern bool Raycast(CPhysicsShape* other, Vector2 startPoint, Vector2 direction, float distance);
extern bool RaycastWithTag(const std::string& tag, Vector2 startPoint, Vector2 direction, float distance, std::vector<CGameObject*>& collidedObjects);

extern bool CircleVsCircle(SCircle& a, SCircle& b);
extern bool BoxVsBox(SBox& a, SBox& b);
extern bool LineVsLine(SLine& a, SLine& b);

extern bool CircleVsBox(SCircle& circle, SBox& box);
extern bool CircleVsLine(SCircle& circle, SLine& line);
extern bool BoxVsLine(SBox& box, SLine& line);
extern bool CheckRayCast(CPhysicsShape* other, SLine& line);

