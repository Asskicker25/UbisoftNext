#include "CDamageAmplifierProjectile.h"

CDamageAmplifierProjectile::CDamageAmplifierProjectile() : CBaseProjectile()
{

	pSprite = App::CreateSprite("Assets/Sprites/Bullet.png", 2, 1);

	pSprite->CreateAnimation(0, 1 / 6, { 0,1 });

	pPhysicsShape = new CPhysicsShape(this, BOX);

	mIsEnabled = false;
	mIsVisible = false;
	mDamageAmount = 2;
}

void CDamageAmplifierProjectile::Start()
{
	CBaseProjectile::Start();
}

void CDamageAmplifierProjectile::Update()
{
	CBaseProjectile::Update();
}

void CDamageAmplifierProjectile::Render()
{
	CBaseProjectile::Render();
}

void CDamageAmplifierProjectile::Cleanup()
{
	CBaseProjectile::Cleanup();
}

void CDamageAmplifierProjectile::OnDestroy()
{
	CBaseProjectile::OnDestroy();
}
