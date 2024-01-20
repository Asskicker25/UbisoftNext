#pragma once

#include "../../Entities/CGameObject.h"

class CPlayerHealthIcon : public CGameObject
{
public:
	CPlayerHealthIcon();
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();
};

