#include "CExplosiveImpactProjectile.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CGameplayManager.h"
#include "../../World/CWorld.h"
#include "../../Physics/Shapes/CPhysicsShapeCircle.h"
#include "../../Player/CPlayerManager.h"
#include "../../TimerEvents/CTimerEventsHandler.h"

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

	CGameObject* collider = new CGameObject();
	collider->pSprite = App::CreateSprite("Assets/Sprites/Circle.png", 1, 1);
	collider->pPhysicsShape = new CPhysicsShape(collider, CIRCLE);
	collider->pPhysicsShape->pShape->SetScale(0.7f, 0.7f);
	collider->mOpacity = 0.3f;


	collider->pSprite->SetScale(3.0f);

	float x, y;
	pSprite->GetPosition(x, y);

	Vector2 pos = Vector2(x, y);

	collider->SetPosition(pos.x, pos.y, true);

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
