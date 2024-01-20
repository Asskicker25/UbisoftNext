#include "CExplosiveImpactProjectile.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CGameplayManager.h"

CExplosiveImpactProjectile::CExplosiveImpactProjectile() : CBaseProjectile()
{
	pSprite = App::CreateSprite("Assets/Sprites/Bomb_strip10.png", 10, 1);

	pSprite->CreateAnimation(0, 1.0f / 6.0f, { 0,1,2,3,4,5,6,7,8,9 });

	pSprite->SetAnimation(0);

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

	int direction = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -1 : 1;
	float angle = pSprite->GetAngle() + CTimer::GetInstance().mDeltaTime * 1.5f * direction;

	pSprite->SetAngle(angle);
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
