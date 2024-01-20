#include "CProjectileFactory.h"
#include "Projectiles/CNormalProjectile.h"

CProjectileFactory::CProjectileFactory()
{
	mNormalProjectile = new CNormalProjectile();
	mNormalProjectile->mName = "Normal Projectile";
}

void CProjectileFactory::Shoot(EProjectileType type, std::vector<Vector2>& arcPath)
{
	switch (type)
	{
	case NORMAL:
		mNormalProjectile->Shoot(arcPath);
		break;
	default:
		break;
	}
}
