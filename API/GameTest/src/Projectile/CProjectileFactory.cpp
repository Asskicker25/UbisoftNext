#include "CProjectileFactory.h"
#include "Projectiles/CNormalProjectile.h"
#include "Projectiles/CDamageAmplifierProjectile.h"
#include "Projectiles/CExplosiveImpactProjectile.h"

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


	mDamageAmplifierProjectile = new CDamageAmplifierProjectile();
	mDamageAmplifierProjectile->mName = "Damage Projectile";

	mDamageAmplifierProjectile->OnProjectileFail.Subscribe("Factory_Destroy", [this]()
		{
			InvokeProjectileFail();
		});

	mDamageAmplifierProjectile->OnProjectileSuccess.Subscribe("Factory_Destroy", [this]()
		{
			InvokeProjectileSuccess();
		});


	mExplosiveImpactProjectile = new CExplosiveImpactProjectile();
	mExplosiveImpactProjectile->mName = "Explosive Projectile";

	mExplosiveImpactProjectile->OnProjectileFail.Subscribe("Factory_Destroy", [this]()
		{
			InvokeProjectileFail();
		});

	mExplosiveImpactProjectile->OnProjectileSuccess.Subscribe("Factory_Destroy", [this]()
		{
			InvokeProjectileSuccess();
		});

}

CProjectileFactory::~CProjectileFactory()
{
	mExplosiveImpactProjectile->Cleanup();
	mDamageAmplifierProjectile->Cleanup();
	mNormalProjectile->Cleanup();
}

void CProjectileFactory::Shoot(EProjectileType type, std::vector<Vector2>& arcPath)
{
	switch (type)
	{
	case NORMAL:
		
		mNormalProjectile->Shoot(arcPath);

		mCurrentProjectile = mNormalProjectile;

		break;

	case EXPLOSIVE_IMPACT_PROJECTILE:

		mExplosiveImpactProjectile->Shoot(arcPath);

		mCurrentProjectile = mExplosiveImpactProjectile;

		break;

	case DAMAGE_AMPLIFIER_PROJECTILE:

		mDamageAmplifierProjectile->Shoot(arcPath);

		mCurrentProjectile = mDamageAmplifierProjectile;

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
