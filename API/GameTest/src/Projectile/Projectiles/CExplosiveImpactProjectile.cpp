#include "CExplosiveImpactProjectile.h"

CExplosiveImpactProjectile::CExplosiveImpactProjectile() : CBaseProjectile()
{
	pSprite = App::CreateSprite("Assets/Sprites/Bullet.png", 2, 1);

	pSprite->CreateAnimation(0, 1 / 6, { 0,1 });

	pPhysicsShape = new CPhysicsShape(this, BOX);

	mIsEnabled = false;
	mIsVisible = false;
}

void CExplosiveImpactProjectile::Start()
{
	CBaseProjectile::Start();
}

void CExplosiveImpactProjectile::Update()
{
	CBaseProjectile::Update();
}

void CExplosiveImpactProjectile::Render()
{
	CBaseProjectile::Render();
}

void CExplosiveImpactProjectile::Cleanup()
{
	CBaseProjectile::Cleanup();
}

void CExplosiveImpactProjectile::OnDestroy()
{
	CBaseProjectile::OnDestroy();
}
