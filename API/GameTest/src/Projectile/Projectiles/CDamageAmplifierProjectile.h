#pragma once

#include "../CBaseProjectile.h"
class CDamageAmplifierProjectile : public CBaseProjectile
{
public:
	CDamageAmplifierProjectile();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();
};

