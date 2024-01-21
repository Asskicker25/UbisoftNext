#include "CPowerUpPickup.h"
#include "../../Utilities/Random.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CPowerUpSpawner.h"
#include "../CPlayerManager.h"


CPowerUpPickup::CPowerUpPickup() : CGameObject()
{

	pSprite = App::CreateSprite("Assets/Sprites/PowerUp_Pickup_strip3.png", 3, 1);

	pSprite->CreateAnimation(0, 1, { 0 });
	pSprite->CreateAnimation(1, 1, { 1 });
	pSprite->CreateAnimation(2, 1, { 2 });

	pPhysicsShape = new CPhysicsShape(this, BOX);

	mCurrentSpeed = GetRandomFloatNumber(mSpeedRange.x, mSpeedRange.y);

}

void CPowerUpPickup::Start()
{
	CGameObject::Start();
}

void CPowerUpPickup::Update()
{

	HandleCollisionCheck();

	float x, y;

	pSprite->GetPosition(x, y);

	y -= CTimer::GetInstance().mDeltaTime * mCurrentSpeed;

	pSprite->SetPosition(x, y);

	if (y <= -50)
	{
		mPowerUpSpawner->RemovePowerUp(this);
	}

	CGameObject::Update();

}

void CPowerUpPickup::Render()
{
	CGameObject::Render();
}

void CPowerUpPickup::Cleanup()
{
	CGameObject::Cleanup();
}

void CPowerUpPickup::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CPowerUpPickup::CopyFromOther(CPowerUpPickup* other)
{
	mPowerUpSpawner = other->mPowerUpSpawner;
	CGameObject::CopyFromOther(other);
}

void CPowerUpPickup::SetPowerUpType(EPowerUp type)
{
	switch (type)
	{
	case NONE:
		break;
	case MAGNIFY:
		pSprite->SetAnimation(0);
		break;
	case DAMAGE_AMPLIFIER:
		pSprite->SetAnimation(2);
		break;
	case EXPLOSIVE_IMPACT:
		pSprite->SetAnimation(1);
		break;
	default:
		break;
	}

	mPowerUpType = type;

}

void CPowerUpPickup::HandleCollisionCheck()
{
	std::vector<CGameObject*> collidedObjects;

	if (CheckCollisionWithTag(pPhysicsShape, "Projectile", collidedObjects))
	{
		CPlayerManager::GetInstance().GetCurrentPlayer()->AddPowerUp(mPowerUpType);
		mPowerUpSpawner->RemovePowerUp(this);
	}
}
