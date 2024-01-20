#include "CNormalProjectile.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CGameplayManager.h"

CNormalProjectile::CNormalProjectile() : CBaseProjectile()
{
	pSprite = App::CreateSprite("Assets/Sprites/Boot.png", 1, 1);

	pSprite->CreateAnimation(0, 1 / 6, { 0,1 });

	pSprite->SetScale(0.75f);

	pPhysicsShape = new CPhysicsShape(this, BOX);

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

	int direction = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -1 : 1;
	float angle = pSprite->GetAngle() + CTimer::GetInstance().mDeltaTime * 5.0f * direction;

	pSprite->SetAngle(angle);
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
