#include "CGameplayManager.h"
#include "../Player/CPlayerManager.h"

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

	SwitchTurn();
}

void CGameplayManager::Update()
{
}

void CGameplayManager::Render()
{
}

void CGameplayManager::Cleanup()
{
}

void CGameplayManager::SwitchTurn()
{
	mCurrentTurn = mCurrentTurn == 1 ? 2 : 1;


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
	return (mCurrentTurn == 1 ? 1 : -1) * mWindDirection * mWindStrength;
}

