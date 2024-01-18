#include "CGameManager.h"
#include "../EntityManager/CEntityManager.h"

// Initiates the game manager and starts the entity manager.
void CGameManager::Start()
{
	CEntityManager::GetInstance().Start();
}

// Updates the entity manager and the current game state (if available).
void CGameManager::Update()
{
	CEntityManager::GetInstance().Update();

	if (pCurrentGameState == nullptr) return;

	pCurrentGameState->Update();
}

//  Renders the entity manager, prints the current game state, and renders the current game state (if available).
void CGameManager::Render()
{
	CEntityManager::GetInstance().Render();

	if (pCurrentGameState == nullptr) return;

	PrintGameState();
	pCurrentGameState->Render();

}

// Adds a new game state to the manager.
void CGameManager::AddState(EGameState state, CGameState* stateInstance)
{
	stateInstance->SetGameManager(this);
	mListOfStates[state] = stateInstance;
}

// Removes a game state from the manager.
void CGameManager::RemoveState(EGameState state)
{
	mListOfStates.erase(state);
}

// Changes the current game state.
void CGameManager::ChangeState(EGameState state)
{
	if (pCurrentGameState != nullptr)
	{
		pCurrentGameState->Cleanup();
	}

	pCurrentGameState = mListOfStates[state];
	eCurrentGameState = state;
	pCurrentGameState->Start();

}

// Cleans up resources and performs necessary tasks before exiting the game.
void CGameManager::Cleanup()
{

	pCurrentGameState->Cleanup();

	std::unordered_map<EGameState, CGameState*>::iterator it;

	for (it = mListOfStates.begin(); it != mListOfStates.end(); ++it)
	{
		delete it->second;
		it->second = nullptr;
	}

	mListOfStates.clear();
}

// Prints the current game state to the console.
void CGameManager::PrintGameState()
{

	switch (eCurrentGameState)
	{
	case MAIN_MENU:
		mGameStateString = "Main Menu";
		break;

	case GAMEPLAY:
		mGameStateString = "Gameplay";
		break;

	case LEVEL_COMPLETE:
		mGameStateString = "Level Complete";
		break;
	}

	App::Print(10, 60, (mGameStateMessage + mGameStateString).c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}
