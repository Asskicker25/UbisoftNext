#include "CGameplayGameState.h"
#include "../../LevelManager/CLevelManager.h"

// Sets up a callback function for the OnNextLevel event in the level manager.
CGameplayGameState::CGameplayGameState()
{
	// Using a lambda function as a callback to show the level complete state when the next level is reached.x
	CLevelManager::GetInstance().OnNextLevel = [this]()
	{
		ShowLevelComplete();
	}; 

}

CGameplayGameState::~CGameplayGameState()
{
	
}

// Initiates the gameplay state by starting the current level.
void CGameplayGameState::Start()
{
	CLevelManager::GetInstance().StartLevel();
}

// Updates the current level in the gameplay state.
void CGameplayGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		CLevelManager::GetInstance().RestartLevel();
	}

	CLevelManager::GetInstance().Update();
}

// Renders the current level in the gameplay state.
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

// Transitions to the level complete state.
void CGameplayGameState::ShowLevelComplete()
{
	ChangeState(LEVEL_COMPLETE);
}
