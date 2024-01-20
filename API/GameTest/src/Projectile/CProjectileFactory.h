#pragma once

#include "CBaseProjectile.h"

class CProjectileFactory
{
public:

	CProjectileFactory();

	void Shoot(EProjectileType type, std::vector<Vector2>& arcPath);

private:
	CBaseProjectile* mNormalProjectile = nullptr;
};

