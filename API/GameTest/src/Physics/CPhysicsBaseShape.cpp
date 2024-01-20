#include "CPhysicsBaseShape.h"

CPhysicsBaseShape::CPhysicsBaseShape()
{
}

CPhysicsBaseShape::CPhysicsBaseShape(CGameObject* gameObject)
{
	this->pGameObject = gameObject;
}

void CPhysicsBaseShape::SetScale(float x, float y)
{
	mScale = Vector2(x,y);
}

void CPhysicsBaseShape::SetOffset(float x, float y)
{
	mOffset = Vector2(x, y);
}

Vector2 CPhysicsBaseShape::GetOffset()
{
	return mOffset;
}

