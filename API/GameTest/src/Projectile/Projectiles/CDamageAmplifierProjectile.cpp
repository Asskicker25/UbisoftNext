#include "CDamageAmplifierProjectile.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CGameplayManager.h"

CDamageAmplifierProjectile::CDamageAmplifierProjectile() : CBaseProjectile()
{

	pSprite = App::CreateSprite("Assets/Sprites/Fish_strip4.png", 4, 1);

	pSprite->CreateAnimation(0, 1.0f / 6.0f, { 0,1,2,3 });

	pSprite->SetAnimation(0);

	pPhysicsShape = new CPhysicsShape(this, BOX);

	mIsEnabled = false;
	mIsVisible = false;
	mDamageAmount = 2;

	pSprite->SetScale(0.75f);
}

void CDamageAmplifierProjectile::Start()
{
	CBaseProjectile::Start();
}

void CDamageAmplifierProjectile::Update()
{
	CBaseProjectile::Update();

	int direction = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -1 : 1;
	float angle = pSprite->GetAngle() + CTimer::GetInstance().mDeltaTime * 5.0f * direction;

	pSprite->SetAngle(angle);
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
