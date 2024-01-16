#include "CPhysicsShape.h"
#include "Shapes/CPhysicsShapeCircle.h"
#include "Shapes/CPhysicsShapeBox.h"

CPhysicsShape::CPhysicsShape(CSimpleSprite* sprite, EPhysicsShape shapeType)
{
	this->mSprite = sprite;
	InitializePhysics(shapeType);
}

void CPhysicsShape::InitializePhysics(EPhysicsShape shapeType)
{
	switch (shapeType)
	{
	case CIRCLE:
		mShape = new CPhysicsShapeCircle(mSprite);
		break;
	case BOX:
		mShape = new CPhysicsShapeBox(mSprite);
		break;
	default:
		break;
	}

}

void CPhysicsShape::Render()
{
	mShape->Render();
}
