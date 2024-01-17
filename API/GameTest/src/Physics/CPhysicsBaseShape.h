#pragma once

#include "../../App/app.h"
#include "Physics_Utils.h"

class CSimpleSprite;

class CPhysicsBaseShape
{
public:

	CPhysicsBaseShape();
	CPhysicsBaseShape(CSimpleSprite* sprite);

	virtual ~CPhysicsBaseShape() {};
	virtual void CalculateShape() = 0;
	virtual void Render() = 0;

	void SetScale(float x, float y);
	void SetOffset(float x, float y);

protected: 
	CSimpleSprite* pSprite = nullptr;

	Vector2 mScale = Vector2(1, 1);
	Vector2 mOffset = Vector2(0, 0);
};

