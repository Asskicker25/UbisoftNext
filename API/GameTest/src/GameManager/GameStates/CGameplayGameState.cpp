#include "CGameplayGameState.h"
#include "../../LevelManager/CLevelManager.h"


CGameplayGameState::CGameplayGameState()
{
	CLevelManager::GetInstance().OnNextLevel = [this]()
	{
		ShowLevelComplete();
	}; 
}

CGameplayGameState::~CGameplayGameState()
{
	
}

void CGameplayGameState::Start()
{
	CLevelManager::GetInstance().StartLevel();
}

void CGameplayGameState::Update()
{
	CLevelManager::GetInstance().Update();
}

void CGameplayGameState::Render()
{
	CLevelManager::GetInstance().Render();
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

void CGameplayGameState::ShowLevelComplete()
{
	ChangeState(LEVEL_COMPLETE);
}
