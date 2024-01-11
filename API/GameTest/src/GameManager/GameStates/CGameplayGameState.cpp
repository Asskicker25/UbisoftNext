#include "CGameplayGameState.h"
#include "../../LevelManager/CLevelManager.h"


CGameplayGameState::~CGameplayGameState()
{
}

void CGameplayGameState::Start()
{
	CLevelManager::GetInstance().Start();
}

void CGameplayGameState::Update()
{
	CLevelManager::GetInstance().Update();
}

void CGameplayGameState::Render()
{
}

void CGameplayGameState::Cleanup()
{
}

void CGameplayGameState::Pause()
{
}

void CGameplayGameState::Resume()
{
}
