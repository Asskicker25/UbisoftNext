#pragma once

#include "CGameObject.h"

class CTextPopUp : public CGameObject
{

public:

	CTextPopUp();
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();
};

