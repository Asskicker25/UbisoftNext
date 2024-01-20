#include "CProjectileFactory.h"
#include "Projectiles/CNormalProjectile.h"

CProjectileFactory::CProjectileFactory()
{
	mNormalProjectile = new CNormalProjectile();
	mNormalProjectile->mName = "Normal Projectile";

	mNormalProjectile->OnProjectileFail.Subscribe("Factory_Destroy", [this]()
		{
			InvokeProjectileFail();
		});

	mNormalProjectile->OnProjectileSuccess.Subscribe("Factory_Destroy", [this]()
		{
			InvokeProjectileSuccess();
		});
}

void CProjectileFactory::Shoot(EProjectileType type, std::vector<Vector2>& arcPath)
{
	switch (type)
	{
	case NORMAL:
		
		mNormalProjectile->Shoot(arcPath);

		mCurrentProjectile = mNormalProjectile;

		break;
	default:
		break;
	}
}

CBaseProjectile* CProjectileFactory::GetCurrentProjectile()
{
	return mCurrentProjectile;
}

void CProjectileFactory::InvokeProjectileSuccess()
{
	OnProjectileSuccess.Invoke();
	mCurrentProjectile = nullptr;
}

void CProjectileFactory::InvokeProjectileFail()
{
	OnProjectileFail.Invoke();

	mCurrentProjectile = nullptr;
}
