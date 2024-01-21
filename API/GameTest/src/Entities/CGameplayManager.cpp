#include "CGameplayManager.h"
#include "../Player/CPlayerManager.h"
#include "../Utilities/Random.h"

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

	SwitchTurn();
}

void CGameplayManager::Update()
{
}

void CGameplayManager::Render()
{
	std::string message = "Round : " + std::to_string(mCurrentRound);
	App::Print(500, 600, message.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	std::string wallSwitchMessage = "Wall Switch in : " + std::to_string(mCurrentWallSwitchRound - mCurrentRound);

	App::Print(500, 500, wallSwitchMessage.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameplayManager::Cleanup()
{
	pPlayerHud->Cleanup();
	mWindHud->Cleanup();
	mPowerUpSpawner->Cleanup();
	mNightManager->Cleanup();
	mCleanedUp = true;
}

void CGameplayManager::SwitchTurn()
{
	if (mCleanedUp) return;

	mCurrentTurn = mCurrentTurn == 1 ? 2 : 1;

	mCurrentRound = mCurrentTurn == 1 ? ++mCurrentRound : mCurrentRound;

	HandleRoundSwitch();
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
			return;
		}
	}

	mWindDirection = GetRandomFloatNumber(-1.0f, 1.0f);
	mWindNoChangeCount = 0;
}

void CGameplayManager::HandleRoundSwitch()
{
	if (mCurrentRound >= mCurrentWallSwitchRound)
	{
		if (mCurrentWallSwitchRound != 0)
		{
			OnWallSwitch.Invoke();
		}
		CalculateRandomRound(mCurrentWallSwitchRound);
	}
}

void CGameplayManager::CalculateRandomRound(int& mRandomRound)
{
	mRandomRound = GetRandomIntNumber(mWallSwitchRoundRange.x, mWallSwitchRoundRange.y);

	mRandomRound += mCurrentRound;
}

