#include "CNormalProjectile.h"

CNormalProjectile::CNormalProjectile() : CBaseProjectile()
{
	pSprite = App::CreateSprite("Assets/Sprites/Bullet.png", 2, 1);

	pSprite->CreateAnimation(0, 1 / 6, { 0,1 });

	mIsEnabled = false;
	mIsVisible = false;
}

void CNormalProjectile::Start()
{
	CBaseProjectile::Start();
}

void CNormalProjectile::Update()
{
	CBaseProjectile::Update();
}

void CNormalProjectile::Render()
{
	CBaseProjectile::Render();
}

void CNormalProjectile::Cleanup()
{
	CBaseProjectile::Cleanup();
}

void CNormalProjectile::OnDestroy()
{
	CBaseProjectile::OnDestroy();
}
