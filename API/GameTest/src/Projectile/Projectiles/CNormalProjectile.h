#pragma once

#include "../CBaseProjectile.h"

class CNormalProjectile : public CBaseProjectile
{
public:

	CNormalProjectile();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

};

