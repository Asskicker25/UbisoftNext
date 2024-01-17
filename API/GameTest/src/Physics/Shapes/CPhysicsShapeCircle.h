#pragma once

#include "../CPhysicsBaseShape.h"

class CPhysicsShapeCircle : public CPhysicsBaseShape
{
public:
	CPhysicsShapeCircle();
	CPhysicsShapeCircle(CSimpleSprite* sprite);
	void CalculateShape() override;
	void Render() override;

	SCircle GetCircle();

	void SetCenter(float x, float y);
	void SetRadius(float radius);
private:
	SCircle mCircle;

};

