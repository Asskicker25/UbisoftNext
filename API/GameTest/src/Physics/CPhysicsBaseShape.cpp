#include "CPhysicsBaseShape.h"

CPhysicsBaseShape::CPhysicsBaseShape()
{
}

CPhysicsBaseShape::CPhysicsBaseShape(CSimpleSprite* sprite)
{
	this->pSprite = sprite;
}

void CPhysicsBaseShape::SetScale(float x, float y)
{
	mScale = Vector2(x,y);
}

void CPhysicsBaseShape::SetOffset(float x, float y)
{
	mOffset = Vector2(x, y);
}

