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

	pPlayerHud = new CPlayerHUD();

	SwitchTurn();
}

void CGameplayManager::Update()
{
}

void CGameplayManager::Render()
{
	std::string message = "Wind : " + std::to_string(mWindDirection);
	App::Print(10, 400, message.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameplayManager::Cleanup()
{
	pPlayerHud->Cleanup();
}

void CGameplayManager::SwitchTurn()
{
	mCurrentTurn = mCurrentTurn == 1 ? 2 : 1;

	HandleWind();

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

