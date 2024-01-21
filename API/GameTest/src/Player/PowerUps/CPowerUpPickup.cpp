#include "CPowerUpPickup.h"
#include "../../Utilities/Random.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CPowerUpSpawner.h"
#include "../CPlayerManager.h"
#include "../../ParticleSystem/CParticleSystem.h"


CPowerUpPickup::CPowerUpPickup() : CGameObject()
{

	pSprite = App::CreateSprite("Assets/Sprites/PowerUp_Pickup_strip3.png", 3, 1);

	pSprite->CreateAnimation(0, 1, { 0 });
	pSprite->CreateAnimation(1, 1, { 1 });
	pSprite->CreateAnimation(2, 1, { 2 });

	pPhysicsShape = new CPhysicsShape(this, BOX);

	mCurrentSpeed = GetRandomFloatNumber(mSpeedRange.x, mSpeedRange.y);

	mOrder = 0;

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

		CParticleSystem* particle = new CParticleSystem("Assets/Sprites/Circle.png", 100, 1);

		float x, y;

		pSprite->GetPosition(x, y);

		particle->SetPosition(x, y, true);
		particle->pSprite->SetScale(0.0f);

		particle->mStartVelocityX = { -300, 300 };
		particle->mStartVelocityY = { -300, 300 };
		particle->mSpawnRadius = 1;
		particle->mStartLifeTime = {0.3,0.5};
		particle->mGravity = -3;
		particle->mScale = 0.05f;
		particle->mColorX = 0;
		particle->mColorY = 0;
		particle->mColorZ = 1;
	}
}
