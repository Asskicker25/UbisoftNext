#pragma once

#include "../CPhysicsBaseShape.h"
#include "../Physics_Utils.h"

class CPhysicsShapeCircle : public CPhysicsBaseShape
{
public:
	CPhysicsShapeCircle(CSimpleSprite* sprite);
	void CalculateShape() override;
	void Render() override;

	SCircle GetCircle();
private:
	SCircle mCircle;

};

