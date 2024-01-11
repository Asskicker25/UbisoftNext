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

	std::unordered_map<EGameState, CGameState*> mListOfStates;

	CGameState* pCurrentGameState = nullptr;
};


