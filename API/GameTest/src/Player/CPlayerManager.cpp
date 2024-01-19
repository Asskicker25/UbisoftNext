#include "CPlayerManager.h"
#include "../Entities/CGameplayManager.h"
#include "../TimerEvents/CTimerEventsHandler.h"


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
}

void CPlayerManager::Cleanup()
{
	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("PManagerTurnStart");
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
	GetCurrentPlayer()->pSprite->SetAnimation(IDLE);
	GetOtherPlayer()->pSprite->SetAnimation(TAUNT);
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

			if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true))
			{
				GetCurrentPlayer()->pSprite->SetAnimation(THROW);

				CGameplayManager::GetInstance().SetState(PLAYER_THROWING);

				//Projectile Spawn
				//Projectile State switch

				CTimerEventsHandler::GetInstance().AddDelay([]()
					{
						CGameplayManager::GetInstance().SwitchTurn();

					}, mThrowingDuration);
			}
		}
		else
		{
			GetCurrentPlayer()->pSprite->SetAnimation(IDLE);
		}
	}
}

