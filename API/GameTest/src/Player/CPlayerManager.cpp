#include "CPlayerManager.h"
#include "../Entities/CGameplayManager.h"
#include "../TimerEvents/CTimerEventsHandler.h"
#include "Arc/CParabolicArc.h"
#include "../Utilities/Remap.h"
#include "../Utilities/Random.h"
#include "../Utilities/Lerp.h"
#include "../Timer/CTimer.h"


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
	pPlayer_One = new CPlayer("Assets/Sprites/Cat_strip35.png");
	pPlayer_One->SetPosition(-mPlayerOffset, 250, true);
	pPlayer_One->mName = "Player 1";

	pPlayer_Two = new CPlayer("Assets/Sprites/CatScaled_strip35.png");
	pPlayer_Two->SetPosition(mPlayerOffset, 250, true);
	pPlayer_Two->mName = "Player 2";

	pProjectileFactory = new CProjectileFactory();

	mCurrentArc = new CArcRenderer(mArcResolution * mArcLength);
	mPrevArc = new CArcRenderer(mArcResolution * mArcLength);
	mPrevArc->UpdateColor(1, 1, 1, 0.4f);

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

	/*std::string message = "Aim Angle : " + std::to_string(mCurrentAngle);

	App::Print(10, 70, message.c_str(), 0.3f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);


	std::string powerUpMessage = "Power Up : ";

	switch (mCurrentPowerUp)
	{
	case NONE:
		powerUpMessage += "NONE";
		break;
	case MAGNIFY:
		powerUpMessage += "MAGNIFY";
		break;
	case DAMAGE_AMPLIFIER:
		powerUpMessage += "DAMAGE_AMPLIFIER";
		break;
	case EXPLOSIVE_IMPACT:
		powerUpMessage += "EXPLOSIVE_IMPACT";
		break;
	default:
		break;
	}
	App::Print(10, 500, powerUpMessage.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);*/

}

void CPlayerManager::Cleanup()
{
	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("PManagerTurnStart");
	pProjectileFactory->OnProjectileSuccess.UnSubscribe("PManagerTurnSwitch");
	pProjectileFactory->OnProjectileFail.UnSubscribe("PManagerTurnSwitch");

	mPrevArc->Cleanup();
	mCurrentArc->Cleanup();

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



bool CPlayerManager::GetPreviousArc(std::vector<Vector2>& prevArc)
{
	if (CGameplayManager::GetInstance().mCurrentTurn == 1)
	{
		if (mPlayerOnePrevArc.size() == 0) return false;

		prevArc = mPlayerOnePrevArc;
	}
	else
	{
		if (mPlayerTwoPrevArc.size() == 0) return false;
		prevArc = mPlayerTwoPrevArc;

	}
	return true;
}

void CPlayerManager::HandleTurnStart()
{
	GetCurrentPlayer()->pSprite->SetAnimation(TAUNT);
	GetOtherPlayer()->pSprite->SetAnimation(IDLE);


	GetCurrentPlayer()->mTag = "Untagged";
	GetOtherPlayer()->mTag = "Player";

	if (pCurrentPowerUp != nullptr)
	{
		pCurrentPowerUp->Deactivate();
		pCurrentPowerUp = nullptr;

		mProjectileType = NORMAL;
	}
}

void CPlayerManager::HandleInput()
{
	if (CGameplayManager::GetInstance().GetState() == PLAYER_AIM)
	{
		HandlePowerUpInput();

		mAimDirection.x = App::GetController().GetLeftThumbStickX();
		mAimDirection.y = App::GetController().GetLeftThumbStickY();

		mAimDirection.Normalize();

		//if (mAimDirection.Magnitude() > 0.1f)
		if (mAimDirection.Magnitude() > 0.1f)
		{
			mAimPressed = true;
		}

		if (mAimPressed)
		{
			GetCurrentPlayer()->pSprite->SetAnimation(AIM);
		}
		else
		{
			GetCurrentPlayer()->pSprite->SetAnimation(TAUNT);
		}

		if (!mAimPressed) return;

		HandleAim();

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true))
		{
			mAimPressed = false;

			if (CGameplayManager::GetInstance().mCurrentTurn == 1)
			{
				mPlayerOnePrevAimY = mCurrentAimY;
				mCurrentAimY = mPlayerTwoPrevAimY;
			}
			else
			{
				mPlayerTwoPrevAimY = mCurrentAimY;
				mCurrentAimY = mPlayerOnePrevAimY;
			}


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
}


void CPlayerManager::HandleAim()
{
	//mCurrentAngle = std::atan2(mAimDirection.y, mAimDirection.x);
	mCurrentAimY += mAimDirection.y * CTimer::GetInstance().mDeltaTime;

	if (mCurrentAimY > 1) { mCurrentAimY = 1; }
	if (mCurrentAimY < 0) { mCurrentAimY = 0; }

	mCurrentAngle = std::atan2(mCurrentAimY, CGameplayManager::GetInstance().mCurrentTurn == 1 ? 1 : -1);

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
		if (mCurrentAngle < 90 + (90 - mAimMaxAngle)) { mCurrentAngle = 90 + mAimMaxAngle; }
	}


	CParabolicArc arc(GetCurrentPlayer()->GetPosition(), mArcResolution, mCurrentAngle, mForce, 10);
	mCurrentArcPositions = arc.GetArc();

}


void CPlayerManager::HandleShoot()
{
	mAimDirection = Vector2(0, 0);

	mCurrentArc->Disable();
	mPrevArc->Disable();

	if (CGameplayManager::GetInstance().mCurrentTurn == 1)
	{
		mPlayerOnePrevArc = mCurrentArcPositions;
	}
	else
	{
		mPlayerTwoPrevArc = mCurrentArcPositions;
	}

	CGameplayManager::GetInstance().SetState(PROJECTILE);

	float windForce = CGameplayManager::GetInstance().GetWindForce();

	CParabolicArc arc(GetCurrentPlayer()->GetPosition(), mArcResolution, mCurrentAngle, mForce + windForce, 10);
	mCurrentArcPositions = arc.GetArc();

	pProjectileFactory->Shoot(mProjectileType, mCurrentArcPositions);

	OnShoot.Invoke();

	PowerUpUsed();
	//CGameplayManager::GetInstance().SwitchTurn();
}


void CPlayerManager::HandleProjectileHit(bool success)
{
	if (success)
	{
		GetOtherPlayer()->pSprite->SetAnimation(HIT_ONE);
		DamagePlayer(pProjectileFactory->GetCurrentProjectile()->mDamageAmount);

		if (GetOtherPlayer()->IsPlayerDead())
		{
			HandlePlayerDead();
			return;
		}
	}
	else
	{
		GetOtherPlayer()->pSprite->SetAnimation(TAUNT);
	}

	HandleSoundOnHit(success);


	CTimerEventsHandler::GetInstance().AddDelay([]()
		{
			CGameplayManager::GetInstance().SwitchTurn();
		}, mProjectHitAnimDuration);
}

void CPlayerManager::HandleSoundOnHit(bool hitPlayer)
{
	switch (mProjectileType)
	{
	case NORMAL:
		App::PlaySound("Assets/Audio/Shoe_hit.wav");
		break;
	case DAMAGE_AMPLIFIER_PROJECTILE:
		App::PlaySound("Assets/Audio/Fish_Hit.wav");
		break;
	case EXPLOSIVE_IMPACT_PROJECTILE:
		App::PlaySound("Assets/Audio/Explosion_sound.wav");
		break;
	default:
		break;
	}

	if (hitPlayer)
	{
		App::PlaySound("Assets/Audio/Cat_Sound_One.wav");
	}

}

void CPlayerManager::DamagePlayer(int amount)
{
	GetOtherPlayer()->ReduceHealth(amount);
	OnPlayerHit.Invoke();
}


void CPlayerManager::RenderArc()
{
	if (CGameplayManager::GetInstance().GetState() == PLAYER_AIM)
	{
		if (mAimPressed)
		{
			mCurrentArc->UpdatePositions(mCurrentArcPositions);

			std::vector<Vector2> prevArc;
			/*int renderCount = mArcLength * mCurrentArcPositions.size();

			for (int i = 1; i < renderCount; i++)
			{
				App::DrawLine(mCurrentArcPositions[i - 1].x, mCurrentArcPositions[i - 1].y,
					mCurrentArcPositions[i].x, mCurrentArcPositions[i].y, 1, 0, 0);
			}*/

			if (GetPreviousArc(prevArc))
			{
				mPrevArc->UpdatePositions(prevArc);
				/*for (int i = 1; i < renderCount; i++)
				{
					App::DrawLine(prevArc[i - 1].x, prevArc[i - 1].y,
						prevArc[i].x, prevArc[i].y, 0, 1, 0);
				}*/
			}
			else
			{
				mPrevArc->Disable();
			}
		}
		else
		{
			mCurrentArc->Disable();
		}

	}

}

void CPlayerManager::HandlePlayerDead()
{
	GetCurrentPlayer()->pSprite->SetAnimation(TAUNT);
	GetOtherPlayer()->pSprite->SetAnimation(HIT_ONE);

	CTimerEventsHandler::GetInstance().AddDelay([this]()
		{
			OnPlayerDead.Invoke();
		}, mLevelEndDuration);
}

void CPlayerManager::HandlePowerUpInput()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		SwitchPowerUp(NONE);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		SwitchPowerUp(DAMAGE_AMPLIFIER);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{

		SwitchPowerUp(EXPLOSIVE_IMPACT);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true))
	{
		SwitchPowerUp(MAGNIFY);
		//PowerUpUsed();

	}
}

bool CPlayerManager::SwitchPowerUp(EPowerUp type)
{

	CBasePowerUp* prevPowerUp = nullptr;

	switch (type)
	{
	case NONE:

		prevPowerUp = pCurrentPowerUp;

		mProjectileType = NORMAL;
		pCurrentPowerUp = nullptr;
		break;


	case MAGNIFY:

		if (GetCurrentPlayer()->mMegaMagnify.second == 0) return false;

		prevPowerUp = pCurrentPowerUp;

		pCurrentPowerUp = GetCurrentPlayer()->mMegaMagnify.first;

		mProjectileType = NORMAL;

		break;

	case DAMAGE_AMPLIFIER:

		if (GetCurrentPlayer()->mDamageAmplifier.second == 0) return false;

		prevPowerUp = pCurrentPowerUp;

		mProjectileType = DAMAGE_AMPLIFIER_PROJECTILE;

		pCurrentPowerUp = GetCurrentPlayer()->mDamageAmplifier.first;
		//GetCurrentPlayer()->mDamageAmplifier.first->Activate();

		break;

	case EXPLOSIVE_IMPACT:

		if (GetCurrentPlayer()->mExplosiveImpact.second == 0) return false;

		prevPowerUp = pCurrentPowerUp;

		mProjectileType = EXPLOSIVE_IMPACT_PROJECTILE;

		pCurrentPowerUp = GetCurrentPlayer()->mExplosiveImpact.first;
		//GetCurrentPlayer()->mExplosiveImpact.first->Activate();

		break;
	}

	mCurrentPowerUp = type;

	return true;

}

void CPlayerManager::PowerUpUsed()
{
	if (pCurrentPowerUp != nullptr)
	{
		pCurrentPowerUp->Activate();
	}

	switch (mCurrentPowerUp)
	{
	case NONE:


		break;
	case MAGNIFY:
		GetCurrentPlayer()->mMegaMagnify.second--;

		break;
	case DAMAGE_AMPLIFIER:

		GetCurrentPlayer()->mDamageAmplifier.second--;

		break;
	case EXPLOSIVE_IMPACT:

		GetCurrentPlayer()->mExplosiveImpact.second--;

		break;
	default:
		break;
	}

	mCurrentPowerUp = NONE;
}
