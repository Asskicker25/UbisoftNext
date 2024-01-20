#pragma once

#include "../../Entities/CGameObject.h"

class CArcDot : public CGameObject
{
public:
	CArcDot();
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

};

