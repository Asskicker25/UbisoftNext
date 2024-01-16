#pragma once

#include "../../App/app.h"

class CSimpleSprite;

class CPhysicsBaseShape
{
public:
	CPhysicsBaseShape(CSimpleSprite* sprite);

	virtual ~CPhysicsBaseShape() {};
	virtual void CalculateShape() = 0;
	virtual void Render() = 0;

	void SetScale(Vector2 scale);

protected: 
	CSimpleSprite* pSprite = nullptr;
	Vector2 mScale = Vector2(1, 1);
};

