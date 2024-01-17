#pragma once
#include "CPhysicsBaseShape.h"

enum EPhysicsShape
{
	CIRCLE,
	BOX,
	LINE
};

class CPhysicsShape
{
public:
	CPhysicsShape(CSimpleSprite* sprite, EPhysicsShape shapeType);
	EPhysicsShape mShapeType = EPhysicsShape::CIRCLE;

	void InitializePhysics(EPhysicsShape shapeType);
	void Render();

	CPhysicsBaseShape* pShape = nullptr;
private:
	CSimpleSprite* pSprite = nullptr;
};

