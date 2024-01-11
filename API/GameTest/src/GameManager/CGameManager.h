#pragma once

#include "CGameState.h"
#include <unordered_map>

class CGameManager
{

public:

	void Start();
	void Update();
	void Render();

	void AddState(EGameState state, CGameState* stateInstance);
	void RemoveState(EGameState state);
	void ChangeState(EGameState state);

	void Cleanup();

private:

	void PrintGameState();

	std::unordered_map<EGameState, CGameState*> mListOfStates;

	CGameState* pCurrentGameState = nullptr;
	EGameState eCurrentGameState = MAIN_MENU;

	const std::string mGameStateMessage = "Current Game State : ";
	std::string mGameStateString;
};


