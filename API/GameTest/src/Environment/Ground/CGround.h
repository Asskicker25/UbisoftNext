#pragma once

#include "../../Entities/CGameObject.h"

class CGround : public CGameObject
{
public:

	CGround();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();
};

