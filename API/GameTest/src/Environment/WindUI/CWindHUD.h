#pragma once

#include "../../Entities/CGameObject.h"

class CWindHUD : public CGameObject
{
public:
	CWindHUD();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	void SetDirection(float direction);


};

