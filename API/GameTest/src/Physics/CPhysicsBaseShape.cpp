#include "CPhysicsBaseShape.h"

CPhysicsBaseShape::CPhysicsBaseShape(CSimpleSprite* sprite)
{
	this->pSprite = sprite;
}

void CPhysicsBaseShape::SetScale(Vector2 scale)
{
	mScale = scale;
}

