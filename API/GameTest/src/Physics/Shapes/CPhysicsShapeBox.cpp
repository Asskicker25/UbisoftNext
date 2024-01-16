#include "CPhysicsShapeBox.h"

CPhysicsShapeBox::CPhysicsShapeBox() : CPhysicsBaseShape()
{
}

CPhysicsShapeBox::CPhysicsShapeBox(CSimpleSprite* sprite) : CPhysicsBaseShape(sprite)
{
	CalculateShape();
}

void CPhysicsShapeBox::CalculateShape()
{

}

SBox CPhysicsShapeBox::GetBox()
{
	CalculateShape();

	return mBox;
}

void CPhysicsShapeBox::Render()
{
}
