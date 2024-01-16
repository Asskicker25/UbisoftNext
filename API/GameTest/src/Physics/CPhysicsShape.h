#pragma once
#include "CPhysicsBaseShape.h"

enum EPhysicsShape
{
	CIRCLE,
	BOX,
};

class CPhysicsShape
{
public:
	CPhysicsShape(CSimpleSprite* sprite, EPhysicsShape shapeType);
	EPhysicsShape mShapeType = EPhysicsShape::CIRCLE;

	void InitializePhysics(EPhysicsShape shapeType);
	void Render();

	CPhysicsBaseShape* mShape = nullptr;
private:
	CSimpleSprite* mSprite = nullptr;
};

