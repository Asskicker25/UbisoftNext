#pragma once

#include "EGameState.h"
#include "../../App/app.h"

class CGameManager;

class CGameState
{
public:

	virtual ~CGameState() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Cleanup() = 0;

	void ChangeState(EGameState state);
	void SetGameManager(CGameManager* gameManger);

private:
	CGameManager* pGameManager = nullptr;

};