#include "CPhysicsShape.h"
#include "../Physics/Shapes/CPhysicsShapeBox.h"
#include "../Physics/Shapes/CPhysicsShapeCircle.h"

CPhysicsShape::CPhysicsShape(CSimpleSprite* sprite, EPhysicsShape shapeType)
{
	this->pSprite = sprite;
	this->mShapeType = shapeType;
	InitializePhysics(shapeType);
}

void CPhysicsShape::InitializePhysics(EPhysicsShape shapeType)
{
	switch (shapeType)
	{
	case CIRCLE:
		pShape = pSprite == nullptr ? new CPhysicsShapeCircle() : new CPhysicsShapeCircle(pSprite);
		break;
	case BOX:
		pShape = pSprite == nullptr ? new CPhysicsShapeBox() :  new CPhysicsShapeBox(pSprite);
		break;
	default:
		break;
	}

}

void CPhysicsShape::Render()
{
	pShape->Render();
}
