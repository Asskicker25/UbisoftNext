#include "CGameplayManager.h"
#include "../Player/CPlayerManager.h"
#include "../Utilities/Random.h"
#include "CNumberUI.h"

CGameplayManager::CGameplayManager()
{
}

CGameplayManager& CGameplayManager::GetInstance()
{
	static CGameplayManager instance;
	return instance;
}

void CGameplayManager::Start()
{
	mCurrentTurn = 2;
	mCleanedUp = false;

	pPlayerHud = new CPlayerHUD();
	mWindHud = new CWindHUD();
	mPowerUpSpawner = new CPowerUpSpawner();
	mNightManager = new CNightManager();

	mRoundUI = new CGameObject();
	mRoundUI->pSprite = App::CreateSprite("Assets/Sprites/Round.png", 1, 1);
	mRoundUI->mIsUI = true;
	mRoundUI->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - 150, true);
	mRoundUI->pSprite->SetScale(0.2f);

	mRoundCountUI = new CNumberUI();
	mRoundCountUI->SetPosition(mRoundCountUIX, APP_VIRTUAL_HEIGHT - 149, true);
	mRoundCountUI->pSprite->SetScale(0.72);



	SwitchTurn();
	HandleRoundSwitch();
}

void CGameplayManager::Update()
{
}

void CGameplayManager::Render()
{
	std::string wallSwitchMessage = "Wall Switch in : " + std::to_string(mCurrentWallSwitchRound - mCurrentRound);

	App::Print(500, 500, wallSwitchMessage.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	std::string nightMessage = "Night in : " + std::to_string(mCurrentNightSwitchRound - mCurrentRound);

	App::Print(500, 450, nightMessage.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameplayManager::Cleanup()
{
	pPlayerHud->Cleanup();
	mWindHud->Cleanup();
	mPowerUpSpawner->Cleanup();
	mNightManager->Cleanup();

	mRoundCountUI->Cleanup();
	mRoundUI->Cleanup();

	mCleanedUp = true;
}

void CGameplayManager::SwitchTurn()
{
	if (mCleanedUp) return;

	mCurrentTurn = mCurrentTurn == 1 ? 2 : 1;

	HandleRoundIncrement();
	HandleWind();

	mWindHud->SetDirection(mWindDirection);

	SetState(PLAYER_AIM);
	OnTurnStart.Invoke();
}

EGameplayState CGameplayManager::GetState()
{
	return mCurrentState;
}

void CGameplayManager::SetState(EGameplayState state)
{
	this->mCurrentState = state;
}

float CGameplayManager::GetWindForce()
{
	//return 1;
	return (mCurrentTurn == 1 ? 1 : -1) * mWindDirection * mWindStrength;
}

void CGameplayManager::HandleWind()
{
	if (mWindNoChangeCount < mWindForceChangeCount)
	{
		int random = GetRandomIntNumber(0, 1);

		if (random == 0)
		{
			mWindNoChangeCount++;

			if (mWindDirection == 0) { mWindDirection = 0.1f; }
			return;
		}
	}

	mWindDirection = GetRandomFloatNumber(-1.0f, 1.0f);
	mWindNoChangeCount = 0;
}

void CGameplayManager::HandleRoundSwitch()
{
	mNightManager->DeActivate();

	if (mCurrentRound >= mCurrentWallSwitchRound)
	{
		if (mCurrentWallSwitchRound != 0)
		{
			OnWallSwitch.Invoke();
		}
		CalculateRandomRound(mCurrentWallSwitchRound, mWallSwitchRoundRange.x, mWallSwitchRoundRange.y);
	}

	if (mCurrentRound >= mCurrentNightSwitchRound)
	{
		if (mCurrentNightSwitchRound != 0)
		{
			mNightManager->Activate();
			//mNightManager.
		}
		CalculateRandomRound(mCurrentNightSwitchRound, mNightSwitchRoundRange.x, mNightSwitchRoundRange.y);
	}



}

void CGameplayManager::HandleRoundIncrement()
{

	if (mCurrentTurn == 1)
	{
		++mCurrentRound;

		mRoundCountUI->SetNumber(mCurrentRound);

		HandleRoundSwitch();
	}
}

void CGameplayManager::CalculateRandomRound(int& mRandomRound, int rangeX, int rangeY)
{
	mRandomRound = GetRandomIntNumber(rangeX, rangeY);

	mRandomRound += mCurrentRound;
}

