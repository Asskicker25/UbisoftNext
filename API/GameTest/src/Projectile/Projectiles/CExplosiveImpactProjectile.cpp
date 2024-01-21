#include "CExplosiveImpactProjectile.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CGameplayManager.h"
#include "../../World/CWorld.h"
#include "../../Physics/Shapes/CPhysicsShapeCircle.h"
#include "../../Player/CPlayerManager.h"
#include "../../TimerEvents/CTimerEventsHandler.h"
#include "../../ParticleSystem/CParticleSystem.h"

CExplosiveImpactProjectile::CExplosiveImpactProjectile() : CBaseProjectile()
{
	pSprite = App::CreateSprite("Assets/Sprites/Bomb_strip10.png", 10, 1);

	pSprite->CreateAnimation(0, 1.0f / 6.0f, { 0,1,2,3,4,5,6,7,8,9 });

	pSprite->SetAnimation(0);

	pPhysicsShape = new CPhysicsShape(this, CIRCLE);

	mIsEnabled = false;
	mIsVisible = false;

	pPhysicsShape->pShape->SetScale(0.5, 0.5);
	pPhysicsShape->pShape->SetOffset(0, -7);
}

void CExplosiveImpactProjectile::Start()
{
	CBaseProjectile::Start();

	CBaseProjectile::OnProjectileSuccess.Subscribe("Success_Explode", [this]()
		{
			Explode(false);
		});

	CBaseProjectile::OnProjectileFail.Subscribe("Fail_Explode", [this]()
		{
			Explode(true);
		});
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
	CBaseProjectile::OnProjectileSuccess.UnSubscribe("Success_Explode");
	CBaseProjectile::OnProjectileFail.UnSubscribe("Fail_Explode");
	CBaseProjectile::Cleanup();
}

void CExplosiveImpactProjectile::OnDestroy()
{
	CBaseProjectile::OnDestroy();
}

void CExplosiveImpactProjectile::Explode(bool doDamage)
{
	/*CParticleSystem* particle = new CParticleSystem("Assets/Sprites/Explosion.png", 100, 6);
	particle->mStartVelocityX = { -200, 200 };
	particle->mStartVelocityY = { -200, 200 };
	particle->mSpawnRadius = 1;
	particle->mStartLifeTime = {1,1};
	particle->mGravity = -5;*/


	CGameObject* collider = new CGameObject();
	collider->pSprite = App::CreateSprite("Assets/Sprites/Explosion_strip7.png", 7, 1);
	collider->pSprite->CreateAnimation(0, 1.0f / 6.0f, { 0,1,2,3,4,5,6 });
	collider->pSprite->SetAnimation(0);
	collider->pPhysicsShape = new CPhysicsShape(collider, CIRCLE);
	collider->pPhysicsShape->pShape->SetScale(0.85, 0.85f);
	collider->mOpacity = 1.0f;
	//collider->pSprite->SetColor(1, 0.3, 0);


	collider->pSprite->SetScale(1.8f);

	float x, y;
	pSprite->GetPosition(x, y);

	Vector2 pos = Vector2(x, y);

	collider->SetPosition(pos.x, pos.y, true);
	//particle->SetPosition(pos.x, pos.y, true);

	std::vector<CGameObject* > collidedObjects;



	if (doDamage)
	{
		if (CheckCollisionWithTag(collider->pPhysicsShape, "Player", collidedObjects))
		{
			CPlayerManager::GetInstance().DamagePlayer(mDamageAmount);
		}
	}

	CTimerEventsHandler::GetInstance().AddDelay([collider]()
		{
			collider->Cleanup();
		}, 1.0f);
}
