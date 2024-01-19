#include "CPhysicsShape.h"
#include "../Physics/Shapes/CPhysicsShapeBox.h"
#include "../Physics/Shapes/CPhysicsShapeCircle.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"
#include "../Entities/CGameObject.h"

CPhysicsShape::CPhysicsShape(CGameObject* gameObject, CPhysicsShape* physicsShape)
{
	this->pGameObject = gameObject;

	this->mShapeType = physicsShape->mShapeType;
	InitializePhysics(mShapeType);
}

CPhysicsShape::CPhysicsShape(CGameObject* gameObject, EPhysicsShape shapeType)
{
	this->pGameObject = gameObject;
	this->mShapeType = shapeType;
	InitializePhysics(mShapeType);
}

CPhysicsShape::~CPhysicsShape()
{
	delete pShape;
}

void CPhysicsShape::InitializePhysics(EPhysicsShape shapeType)
{
	switch (shapeType)
	{
	case CIRCLE:
		pShape = pGameObject->pSprite == nullptr ? new CPhysicsShapeCircle() : new CPhysicsShapeCircle(pGameObject);
		break;
	case BOX:
		pShape = pGameObject->pSprite == nullptr ? new CPhysicsShapeBox() :  new CPhysicsShapeBox(pGameObject);
		break;
	case LINE : 
		pShape = new CPhysicsShapeLine();
	default:
		break;
	}

}

void CPhysicsShape::Render()
{
	pShape->Render();
}
