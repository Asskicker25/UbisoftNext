#pragma once

#include "../CPhysicsBaseShape.h"

class CPhysicsShapeLine : public CPhysicsBaseShape
{
public:
	CPhysicsShapeLine();

	void CalculateShape() override;
	void Render() override;

	SLine GetLine();

	void SetLine(float sx, float sy, float ex, float ey);

private:
	SLine mLine;
};

