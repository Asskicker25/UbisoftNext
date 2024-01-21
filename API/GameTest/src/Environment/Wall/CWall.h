#pragma once

#include "../../Entities/CGameObject.h"

class CWall : public CGameObject
{
public:

	CWall();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	void ChangePosition();

	Vector2 mYRange;

};

