#include "CPlayerManager.h"
#include "../Entities/CGameplayManager.h"
#include "../TimerEvents/CTimerEventsHandler.h"
#include "Arc/CParabolicArc.h"
#include "../Utilities/Remap.h"


CPlayerManager::CPlayerManager()
{
}

CPlayerManager::~CPlayerManager()
{
}

CPlayerManager& CPlayerManager::GetInstance()
{
	static CPlayerManager instance;
	return instance;
}

void CPlayerManager::Start()
{
	pPlayer_One = new CPlayer();
	pPlayer_One->SetPosition(-mPlayerOffset, 250, true);
	pPlayer_One->mName = "Player 1";

	pPlayer_Two = new CPlayer();
	pPlayer_Two->SetPosition(mPlayerOffset, 250, true);
	pPlayer_Two->mName = "Player 2";

	pProjectileFactory = new CProjectileFactory();

	pProjectileFactory->OnProjectileSuccess.Subscribe("PManagerTurnSwitch", [this]()
		{
			HandleProjectileHit(true);
		});

	pProjectileFactory->OnProjectileFail.Subscribe("PManagerTurnSwitch", [this]()
		{
			HandleProjectileHit(false);
		});

	CGameplayManager::GetInstance().OnTurnStart.Subscribe("PManagerTurnStart", [this]()
		{
			HandleTurnStart();
		});

}

void CPlayerManager::Update()
{
	HandleInput();
}

void CPlayerManager::Render()
{
	RenderArc();

	std::string message = "Aim Angle : " + std::to_string(mCurrentAngle);

	App::Print(10, 70, message.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CPlayerManager::Cleanup()
{
	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("PManagerTurnStart");
	pProjectileFactory->OnProjectileSuccess.UnSubscribe("PManagerTurnSwitch");
	pProjectileFactory->OnProjectileFail.UnSubscribe("PManagerTurnSwitch");

	pPlayer_One->Cleanup();
	pPlayer_Two->Cleanup();
}

CPlayer* CPlayerManager::GetCurrentPlayer()
{
	return CGameplayManager::GetInstance().mCurrentTurn == 1 ? pPlayer_One : pPlayer_Two;
}

CPlayer* CPlayerManager::GetOtherPlayer()
{
	return CGameplayManager::GetInstance().mCurrentTurn == 1 ? pPlayer_Two : pPlayer_One;
}

void CPlayerManager::HandleTurnStart()
{
	GetCurrentPlayer()->pSprite->SetAnimation(TAUNT);
	GetOtherPlayer()->pSprite->SetAnimation(IDLE);

	GetCurrentPlayer()->mTag = "Untagged";
	GetOtherPlayer()->mTag = "Player";
}

void CPlayerManager::HandleInput()
{
	if (CGameplayManager::GetInstance().GetState() == PLAYER_AIM)
	{
		mAimDirection.x = App::GetController().GetLeftThumbStickX();
		mAimDirection.y = App::GetController().GetLeftThumbStickY();

		mAimDirection.Normalize();

		if (mAimDirection.Magnitude() > 0.1f)
		{
			GetCurrentPlayer()->pSprite->SetAnimation(AIM);

			HandleAim();

			if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true))
			{
				GetCurrentPlayer()->pSprite->SetAnimation(THROW);

				CGameplayManager::GetInstance().SetState(PLAYER_THROWING);

				CTimerEventsHandler::GetInstance().AddDelay([this]()
					{
						HandleShoot();
					},
					mThrowingDuration);

				CTimerEventsHandler::GetInstance().AddDelay([this]()
					{
						GetCurrentPlayer()->pSprite->SetAnimation(IDLE);
					},
					mThrowingDuration * 5);
			}
		}
		else
		{
			GetCurrentPlayer()->pSprite->SetAnimation(TAUNT);
		}
	}
}


void CPlayerManager::HandleAim()
{
	mCurrentAngle = std::atan2(mAimDirection.y, mAimDirection.x);

	mCurrentAngle = mCurrentAngle * 180.0 / PI;


	if (CGameplayManager::GetInstance().mCurrentTurn == 1)
	{
		if (mCurrentAngle < mAimMinAngle) { mCurrentAngle = mAimMinAngle; }
		if (mCurrentAngle > mAimMaxAngle) { mCurrentAngle = mAimMaxAngle; }
	}
	else
	{
		if (mCurrentAngle < 0)
		{
			mCurrentAngle += 360.0;
		}

		if (mCurrentAngle > 180 - mAimMinAngle) { mCurrentAngle = 180 - mAimMinAngle; }
		if (mCurrentAngle < 90 + mAimMaxAngle) { mCurrentAngle = 90 + mAimMaxAngle; }
	}


	CParabolicArc arc(GetCurrentPlayer()->GetPosition(), mArcResolution, mCurrentAngle, mForce, 10);
	mCurrentArcPositions = arc.GetArc();

}

void CPlayerManager::HandleShoot()
{
	mAimDirection = Vector2(0, 0);
	CGameplayManager::GetInstance().SetState(PROJECTILE);

	float windForce = CGameplayManager::GetInstance().GetWindForce();

	CParabolicArc arc(GetCurrentPlayer()->GetPosition(), mArcResolution, mCurrentAngle, mForce + windForce, 10);
	mCurrentArcPositions = arc.GetArc();

	pProjectileFactory->Shoot(NORMAL, mCurrentArcPositions);
	OnShoot.Invoke();
	//CGameplayManager::GetInstance().SwitchTurn();
}


void CPlayerManager::HandleProjectileHit(bool success)
{
	if (success)
	{
		GetOtherPlayer()->pSprite->SetAnimation(HIT_ONE);
		GetOtherPlayer()->ReduceHealth(1);
		OnPlayerHit.Invoke();
	}
	else
	{
		GetOtherPlayer()->pSprite->SetAnimation(TAUNT);
	}


	CTimerEventsHandler::GetInstance().AddDelay([]()
		{
			CGameplayManager::GetInstance().SwitchTurn();
		}, mProjectHitAnimDuration);
}


void CPlayerManager::RenderArc()
{
	if (CGameplayManager::GetInstance().GetState() == PLAYER_AIM)
	{
		if (mAimDirection.Magnitude() > 0.1f)
		{
			int renderCount = mArcLength * mCurrentArcPositions.size();

			for (int i = 1; i < renderCount; i++)
			{
				App::DrawLine(mCurrentArcPositions[i - 1].x, mCurrentArcPositions[i - 1].y,
					mCurrentArcPositions[i].x, mCurrentArcPositions[i].y, 0, 1, 0);
			}
		}

	}

}

