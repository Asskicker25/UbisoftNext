#pragma once

#include "CBaseProjectile.h"

class CProjectileFactory
{
public:

	CProjectileFactory();

	void Shoot(EProjectileType type, std::vector<Vector2>& arcPath);

	CBaseProjectile* GetCurrentProjectile();
	
	CEvents OnProjectileSuccess;
	CEvents OnProjectileFail;

private:

	void InvokeProjectileFail();
	void InvokeProjectileSuccess();

	CBaseProjectile* mCurrentProjectile = nullptr;
	CBaseProjectile* mNormalProjectile = nullptr;
};

