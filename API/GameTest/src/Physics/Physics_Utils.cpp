#include "Physics_Utils.h"
#include "Shapes/CPhysicsShapeBox.h"
#include "Shapes/CPhysicsShapeCircle.h"
#include "Shapes/CPhysicsShapeLine.h"
#include "CPhysicsShape.h"
#include "../EntityManager/CEntityManager.h"
#include "../Entities/CGameObject.h"


bool CheckCollision(CPhysicsShape* a, CPhysicsShape* b)
{
	if (a == nullptr || b == nullptr || a == b) return false;

	switch (a->mShapeType)
	{
#pragma region CIRCLE

	case CIRCLE:

		switch (b->mShapeType)
		{
		case CIRCLE:
			return CircleVsCircle(dynamic_cast<CPhysicsShapeCircle*>(a->pShape)->GetCircle(),
				dynamic_cast<CPhysicsShapeCircle*>(b->pShape)->GetCircle());

		case BOX: 

			return CircleVsBox(dynamic_cast<CPhysicsShapeCircle*>(a->pShape)->GetCircle(),
				dynamic_cast<CPhysicsShapeBox*>(b->pShape)->GetBox());

		case LINE: 
			return CircleVsLine(dynamic_cast<CPhysicsShapeCircle*>(a->pShape)->GetCircle(),
				dynamic_cast<CPhysicsShapeLine*>(b->pShape)->GetLine());
		}

		break;

#pragma endregion

#pragma region BOX

	case BOX:

		switch (b->mShapeType)
		{
		case CIRCLE:

			return CircleVsBox(dynamic_cast<CPhysicsShapeCircle*>(b->pShape)->GetCircle(),
				dynamic_cast<CPhysicsShapeBox*>(a->pShape)->GetBox());

		case BOX:

			return BoxVsBox(dynamic_cast<CPhysicsShapeBox*>(a->pShape)->GetBox(),
				dynamic_cast<CPhysicsShapeBox*>(b->pShape)->GetBox());

		case LINE:
			return BoxVsLine(dynamic_cast<CPhysicsShapeBox*>(a->pShape)->GetBox(),
				dynamic_cast<CPhysicsShapeLine*>(b->pShape)->GetLine());
		}

		break;

#pragma endregion

#pragma region LINE
	case LINE:

		switch (b->mShapeType)
		{
		case CIRCLE:
			return CircleVsLine(dynamic_cast<CPhysicsShapeCircle*>(b->pShape)->GetCircle(),
				dynamic_cast<CPhysicsShapeLine*>(a->pShape)->GetLine());

		case BOX:

			return BoxVsLine(dynamic_cast<CPhysicsShapeBox*>(b->pShape)->GetBox(),
				dynamic_cast<CPhysicsShapeLine*>(a->pShape)->GetLine());

		case LINE:
			return LineVsLine(dynamic_cast<CPhysicsShapeLine*>(a->pShape)->GetLine(),
				dynamic_cast<CPhysicsShapeLine*>(b->pShape)->GetLine());
		}

		break;
#pragma endregion

	}


	return false;
}


bool CheckRayCast(CPhysicsShape* a, SLine& line)
{
	if (a == nullptr) return false;

	switch (a->mShapeType)
	{

	case CIRCLE:

		return CircleVsLine(dynamic_cast<CPhysicsShapeCircle*>(a->pShape)->GetCircle(), line);

	case BOX:

		return BoxVsLine(dynamic_cast<CPhysicsShapeBox*>(a->pShape)->GetBox(), line);

	case LINE:

		return LineVsLine(dynamic_cast<CPhysicsShapeLine*>(a->pShape)->GetLine(), line);

	}

	return false;
}


bool CheckCollisionWithTag(CPhysicsShape* a, const std::string& tag, std::vector<CGameObject*>& collidedObjects)
{
	std::vector<CEntity*> listOfEntities = CEntityManager::GetInstance().GetEntitiesWithTag(tag);

	for (CEntity* entity : listOfEntities)
	{
		if (!entity->mIsEnabled) continue;

		if (CGameObject* gameObject = dynamic_cast<CGameObject*> (entity))
		{
			if (CheckCollision(a, gameObject->pPhysicsShape))
			{
				collidedObjects.push_back(gameObject);
			}
		}
	}

	if (collidedObjects.size() == 0) return false;

	return true;
}

bool Raycast(CPhysicsShape* a, Vector2 startPoint, Vector2 direction, float distance)
{
	SLine line;
	line.mStartPoint = startPoint;
	line.mEndPoint = startPoint + (direction * distance);

	if (CheckRayCast(a, line)) return true;

	return false;
}

bool RaycastWithTag(const std::string& tag, Vector2 startPoint, Vector2 direction, float distance, std::vector<CGameObject*>& collidedObjects)
{
	std::vector<CEntity*> listOfEntities = CEntityManager::GetInstance().GetEntitiesWithTag(tag);

	SLine line;
	line.mStartPoint = startPoint;
	line.mEndPoint = startPoint + (direction * distance);

	for (CEntity* entity : listOfEntities)
	{
		if (!entity->mIsEnabled) continue;

		if (CGameObject* gameObject = dynamic_cast<CGameObject*> (entity))
		{
			if (CheckRayCast(gameObject->pPhysicsShape, line))
			{
				collidedObjects.push_back(gameObject);
			}
		}
	}

	if (collidedObjects.size() == 0) return false;

	return true;
}

bool CircleVsCircle(SCircle& a, SCircle& b)
{
	Vector2 diff = a.mCenter - b.mCenter;

	float distanceSquared = diff.x * diff.x + diff.y * diff.y;

	float radiiSumSquared = (a.mRadius + b.mRadius) * (a.mRadius + b.mRadius);

	return distanceSquared < radiiSumSquared;
}

bool BoxVsBox(SBox& a, SBox& b)
{
    if (a.mMaxPoint.x < b.mMinPoint.x || a.mMinPoint.x > b.mMaxPoint.x ||
        a.mMaxPoint.y < b.mMinPoint.y || a.mMinPoint.y > b.mMaxPoint.y)
    {
        return false;
    }

    return true;
}

bool LineVsLine(SLine& a, SLine& b)
{
	Vector2 dirA = { a.mEndPoint.x - a.mStartPoint.x, a.mEndPoint.y - a.mStartPoint.y };
	Vector2 dirB = { b.mEndPoint.x - b.mStartPoint.x, b.mEndPoint.y - b.mStartPoint.y };

	float crossProduct = (dirA.x * dirB.y) - (dirA.y * dirB.x);

	if (std::abs(crossProduct) < 1e-6)
	{
		return false;
	}

	Vector2 startVec = { b.mStartPoint.x - a.mStartPoint.x, b.mStartPoint.y - a.mStartPoint.y };

	float t = (startVec.x * dirB.y - startVec.y * dirB.x) / crossProduct;
	float u = (startVec.x * dirA.y - startVec.y * dirA.x) / crossProduct;

	return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool CircleVsBox(SCircle& circle, SBox& box)
{
	float closestX = max(box.mMinPoint.x, min(circle.mCenter.x, box.mMaxPoint.x));
	float closestY = max(box.mMinPoint.y, min(circle.mCenter.y, box.mMaxPoint.y));

	float distanceX = circle.mCenter.x - closestX;
	float distanceY = circle.mCenter.y - closestY;

	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (circle.mRadius * circle.mRadius);
}

bool CircleVsLine(SCircle& circle, SLine& line)
{
	Vector2 lineToCircle = { circle.mCenter.x - line.mStartPoint.x, circle.mCenter.y - line.mStartPoint.y };

	Vector2 lineDirection = { line.mEndPoint.x - line.mStartPoint.x, line.mEndPoint.y - line.mStartPoint.y };

	float t = (lineToCircle.x * lineDirection.x + lineToCircle.y * lineDirection.y) /
		(lineDirection.x * lineDirection.x + lineDirection.y * lineDirection.y);

	t = max(0.0f, min(t, 1.0f));

	Vector2 closestPoint = { line.mStartPoint.x + t * lineDirection.x, line.mStartPoint.y + t * lineDirection.y };

	float distanceSquared = pow(circle.mCenter.x - closestPoint.x, 2) + pow(circle.mCenter.y - closestPoint.y, 2);
	float radiusSquared = pow(circle.mRadius, 2);

	return distanceSquared <= radiusSquared;
}

bool BoxVsLine(SBox& box, SLine& line)
{
	if ((line.mStartPoint.x > box.mMaxPoint.x && line.mEndPoint.x > box.mMaxPoint.x) ||
		(line.mStartPoint.x < box.mMinPoint.x && line.mEndPoint.x < box.mMinPoint.x) ||
		(line.mStartPoint.y > box.mMaxPoint.y && line.mEndPoint.y > box.mMaxPoint.y) ||
		(line.mStartPoint.y < box.mMinPoint.y && line.mEndPoint.y < box.mMinPoint.y))
	{
		return false;
	}

	// Check if the line intersects any of the box's edges
	SLine boxEdges[4] = {
		{box.mMinPoint, {box.mMaxPoint.x, box.mMinPoint.y}},
		{{box.mMaxPoint.x, box.mMinPoint.y}, box.mMaxPoint},
		{box.mMaxPoint, {box.mMinPoint.x, box.mMaxPoint.y}},
		{{box.mMinPoint.x, box.mMaxPoint.y}, box.mMinPoint}
	};

	for (int i = 0; i < 4; ++i)
	{
		if (LineVsLine(line, boxEdges[i]))
			return true;
	}

	return false;
}

