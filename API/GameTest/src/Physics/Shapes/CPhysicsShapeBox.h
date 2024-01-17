#pragma once

#include "../CPhysicsBaseShape.h"

class CPhysicsShapeBox : public CPhysicsBaseShape
{
public:
	CPhysicsShapeBox();
	CPhysicsShapeBox(CSimpleSprite* sprite);
	void CalculateShape() override;
	void Render() override;

	SBox GetBox();


private:
	SBox mBox;
};

