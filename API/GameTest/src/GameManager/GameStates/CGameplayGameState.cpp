#include "CGameplayGameState.h"
#include "../../LevelManager/CLevelManager.h"
#include "../../Tween/CTweenManager.h"

// Sets up a callback function for the OnNextLevel event in the level manager.
CGameplayGameState::CGameplayGameState()
{
	// Using a lambda function as a callback to show the level complete state when the next level is reached.
	CLevelManager::GetInstance().OnNextLevel.Subscribe("ShowLevelComplete", [this]()
		{
			ShowLevelComplete();

		});

}

CGameplayGameState::~CGameplayGameState()
{
	CLevelManager::GetInstance().OnNextLevel.UnSubscribe("ShowLevelComplete");
}

// Initiates the gameplay state by starting the current level.
void CGameplayGameState::Start()
{
	CLevelManager::GetInstance().StartLevel();
	App::PlaySound("Assets/Audio/BGM.wav", true);

}

// Updates the current level in the gameplay state.
void CGameplayGameState::Update()
{
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		CLevelManager::GetInstance().RestartLevel();
	}*/

	CLevelManager::GetInstance().Update();

}

// Renders the current level in the gameplay state.
void CGameplayGameState::Render()
{
	CLevelManager::GetInstance().Render();
}

void CGameplayGameState::Cleanup()
{
	App::StopSound("Assets/Audio/BGM.wav");
	CTweenManager::GetInstance().Cleanup();
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
