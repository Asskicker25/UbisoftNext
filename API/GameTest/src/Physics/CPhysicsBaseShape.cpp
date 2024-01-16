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

