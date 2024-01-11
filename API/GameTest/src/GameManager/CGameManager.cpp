#include "CGameManager.h"

void CGameManager::Start()
{
}

void CGameManager::Update()
{
	if (pCurrentGameState == nullptr) return;

	pCurrentGameState->Update();
}

void CGameManager::Render()
{
	if (pCurrentGameState == nullptr) return;
	
	pCurrentGameState->Render();

}

void CGameManager::AddState(EGameState state, CGameState* stateInstance)
{
	stateInstance->SetGameManager(this);
	mListOfStates[state] = stateInstance;
}

void CGameManager::RemoveState(EGameState state)
{
	mListOfStates.erase(state);
}

void CGameManager::ChangeState(EGameState state)
{
	if (pCurrentGameState != nullptr)
	{
		pCurrentGameState->Cleanup();
	}

	pCurrentGameState = mListOfStates[state];
	pCurrentGameState->Start();

}

void CGameManager::Cleanup()
{
	pCurrentGameState->Cleanup();
}
