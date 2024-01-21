#include "CNightManager.h"

#include "CGameplayManager.h"
#include "../Player/CPlayerManager.h"

#include "../Tween/CTweenManager.h"
#include "../TimerEvents/CTimerEventsHandler.h"
#include <iostream>
#include "../World/CWorld.h"

CNightManager::CNightManager() : CGameObject()
{

	mNightSprite = new CGameObject();

	mNightSprite->pSprite = App::CreateSprite("Assets/Sprites/NightBG.png", 1, 1);
	mNightSprite->SetPosition(-600, 250, true);
	mNightSprite->mOpacity = 0.96f;
	mNightSprite->mOrder = 1;
	mNightSprite->pSprite->SetScale(3);

	CGameplayManager::GetInstance().OnTurnStart.Subscribe("Night_Start", [this]()
		{
			OnTurnStart();
		});

	CPlayerManager::GetInstance().OnShoot.Subscribe("Night_Follow", [this]()
		{
			OnFollowProjectile();
		});


	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileSuccess.Subscribe("ProjectileHit", [this]()
		{
			OnProjectileHit();
		});

	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileFail.Subscribe("ProjectileHit", [this]()
		{
			OnProjectileHit();
		});

	DeActivate();

	//mNightSprite->pSprite->SetScale(0.1f);
}

void CNightManager::Start()
{
	CGameObject::Start();
}

void CNightManager::Update()
{
	HandleProjectileFollow();
	CGameObject::Update();
}

void CNightManager::Render()
{
	CGameObject::Render();
}

void CNightManager::Cleanup()
{
	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("Night_Start");
	CPlayerManager::GetInstance().OnShoot.UnSubscribe("Night_Follow");

	 
	if (CPlayerManager::GetInstance().pProjectileFactory != nullptr)
	{
		CPlayerManager::GetInstance().pProjectileFactory->OnProjectileSuccess.UnSubscribe("ProjectileHit");
		CPlayerManager::GetInstance().pProjectileFactory->OnProjectileFail.UnSubscribe("ProjectileHit");
	}
	

	mNightSprite->Cleanup();

	CGameObject::Cleanup();
}

void CNightManager::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CNightManager::Activate()
{
	mNightSprite->mIsVisible = true;
	mIsEnabled = true;
}

void CNightManager::DeActivate()
{
	mNightSprite->mIsVisible = false;
	mIsEnabled = false;
}

void CNightManager::OnTurnStart()
{
	CPlayer* player = CPlayerManager::GetInstance().GetCurrentPlayer();

	Vector2 pos = player->GetPosition();
	pos.x -= 10;

	mNightSprite->SetPosition(pos.x, pos.y);
}

void CNightManager::OnFollowProjectile()
{
	mCanFollow = true;
	mCurrentProjectile = CPlayerManager::GetInstance().pProjectileFactory->GetCurrentProjectile();
}

void CNightManager::HandleProjectileFollow()
{
	if (!mCanFollow) return;

	Vector2 pos = mCurrentProjectile->GetPosition();

	pos.x -= 10;

	mNightSprite->SetPosition(pos.x, pos.y);
}

void CNightManager::OnProjectileHit()
{
	mCanFollow = false;



	Vector2 nightPos = mNightSprite->GetPosition();

	CPlayer* player = CPlayerManager::GetInstance().GetOtherPlayer();

	Vector2 pos = player->GetPosition();
	pos.x -= 10;

	mOriginInitPos = CWorld::GetInstance().mOrigin;


	CTweenManager::GetInstance().AddFloatTween(nightPos.x, pos.x, 1, [this](float value)
		{
			Vector2 nightPos1 = mNightSprite->GetPosition();

			Vector2 currentCamera = CWorld::GetInstance().mOrigin;

			Vector2 offset = currentCamera - mOriginInitPos;

			value -= offset.x;

			mNightSprite->SetPosition(value, nightPos1.y);
		});


	CTweenManager::GetInstance().AddFloatTween(nightPos.y, pos.y, 1, [this](float value)
		{
			Vector2 nightPos1 = mNightSprite->GetPosition();

			Vector2 currentCamera = CWorld::GetInstance().mOrigin;

			Vector2 offset = currentCamera - mOriginInitPos;

			value -= offset.y;

			mNightSprite->SetPosition(nightPos1.x, value);
		});



}
