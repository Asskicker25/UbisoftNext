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

	PrintGameState();
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
	eCurrentGameState = state;
	pCurrentGameState->Start();

}

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
