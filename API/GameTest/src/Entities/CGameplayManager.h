#pragma once

#include "../Events/Events.h"

enum EGameplayState
{
	PLAYER_AIM = 0,
	PLAYER_THROWING = 1, 
	PROJECTILE = 2,

};

class CGameplayManager
{

public:

	CGameplayManager();

	static CGameplayManager& GetInstance();
	
	// Inherited via CEntity
	void Start();
	void Update();
	void Render();
	void Cleanup();

	void SwitchTurn();

	EGameplayState GetState();
	void SetState(EGameplayState state);

	CEvents OnTurnStart;
	EGameplayState mCurrentState = PLAYER_AIM;

	int mCurrentTurn = 1;
};

