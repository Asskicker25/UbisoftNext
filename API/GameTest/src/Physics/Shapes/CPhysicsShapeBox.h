#pragma once

#include "../CPhysicsBaseShape.h"
#include "../Physics_Utils.h"

class CPhysicsShapeBox : public CPhysicsBaseShape
{
public:
	CPhysicsShapeBox(CSimpleSprite* sprite);
	void CalculateShape() override;
	void Render() override;

	SBox GetBox();

private:
	SBox mBox;
};

