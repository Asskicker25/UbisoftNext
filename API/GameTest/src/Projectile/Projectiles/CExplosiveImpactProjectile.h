#pragma once

#include "../CBaseProjectile.h"

class CExplosiveImpactProjectile : public CBaseProjectile
{
public:

	CExplosiveImpactProjectile();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();
};

