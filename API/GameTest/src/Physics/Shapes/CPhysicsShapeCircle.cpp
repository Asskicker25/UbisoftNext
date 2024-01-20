#include "CPhysicsShapeCircle.h"
#include "../../Entities/CGameObject.h"

CPhysicsShapeCircle::CPhysicsShapeCircle() : CPhysicsBaseShape()
{
}

CPhysicsShapeCircle::CPhysicsShapeCircle(CGameObject* gameObject) : CPhysicsBaseShape(gameObject)
{
	CalculateShape();
}

void CPhysicsShapeCircle::CalculateShape()
{

	// Sets the sprite position as the Circle center

	Vector2 pos = pGameObject->GetPosition();

	mCircle.mCenter = pos;

	// Calculates radius from the sprite height and widht
	float height = pGameObject->pSprite->GetHeight();
	float width = pGameObject->pSprite->GetWidth();

	float radius = height;

	radius = (width > height ? width * 0.5f : radius * 0.5f);

	mCircle.mRadius = radius;
}

SCircle CPhysicsShapeCircle::GetCircle()
{
	SCircle circle = mCircle;

	// Updates the center of the circle if a sprite is assosicated to the shape
	if (pGameObject != nullptr)
	{
		if (pGameObject->pSprite != nullptr)
		{
			Vector2 pos = pGameObject->GetPosition();

			circle.mCenter = pos;
			circle.mRadius *= pGameObject->pSprite->GetScale();
		}
	}
	

	// Updates the center of the circle with the offset
	circle.mCenter = circle.mCenter + mOffset;

	// Updates the radius based on the scale
	circle.mRadius *= mScale.x;

	return circle;
}

void CPhysicsShapeCircle::SetCenter(float x, float y)
{
	mCircle.mCenter = Vector2(x, y);
}

void CPhysicsShapeCircle::SetRadius(float radius)
{
	mCircle.mRadius = radius;
}

void CPhysicsShapeCircle::Render()
{
	SCircle circle =  GetCircle();

	float cx = circle.mCenter.x;
	float cy = circle.mCenter.y;
	float radius = circle.mRadius;

	float theta = 0;
	float step = 0.01f; 

	while (theta <= 2 * 3.14159)
	{
		float x1 = cx + radius * cos(theta);
		float y1 = cy + radius * sin(theta);

		theta += step;

		float x2 = cx + radius * cos(theta);
		float y2 = cy + radius * sin(theta);

		App::DrawLine(x1, y1, x2, y2, 0, 1, 0);
	}
}
