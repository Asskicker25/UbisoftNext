#include "Physics_Utils.h"
#include "Shapes/CPhysicsShapeBox.h"
#include "Shapes/CPhysicsShapeCircle.h"

bool CheckCollision(CPhysicsShape& a, CPhysicsShape& b)
{
	switch (a.mShapeType)
	{
#pragma region CIRCLE

	case CIRCLE:

		switch (b.mShapeType)
		{
		case CIRCLE:
			return CircleVsCircle(dynamic_cast<CPhysicsShapeCircle*>(a.pShape)->GetCircle(),
				dynamic_cast<CPhysicsShapeCircle*>(b.pShape)->GetCircle());

		case BOX: 
			break;
		}

		break;

#pragma endregion

#pragma region BOX

	case BOX:

		switch (b.mShapeType)
		{
		case CIRCLE:
			break;
		case BOX:
			break;
		}

		break;

#pragma endregion
	
	}


	return false;
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
