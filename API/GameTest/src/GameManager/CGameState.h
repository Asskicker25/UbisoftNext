#pragma once

#include "EGameState.h"
#include "../../App/app.h"
#include <string>

class CGameManager;

class CGameState
{
public:

	virtual ~CGameState() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	void ChangeState(EGameState state);
	void SetGameManager(CGameManager* gameManger);

private:
	
	bool mIsPaused = false;
	CGameManager* pGameManager = nullptr;

};