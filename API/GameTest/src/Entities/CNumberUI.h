#pragma once

#include "CGameObject.h"

class CNumberUI : public CGameObject
{

public:
	CNumberUI();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	void SetNumber(int number);
};

