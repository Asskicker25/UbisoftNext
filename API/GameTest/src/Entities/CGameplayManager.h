#pragma once

#include "../Events/Events.h"
#include "../Player/UI/CPlayerHUD.h"

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

	float GetWindForce();

	CEvents OnTurnStart;
	EGameplayState mCurrentState = PLAYER_AIM;

	CPlayerHUD* pPlayerHud;

	int mCurrentTurn = 1;

	int mWindStrength = 10;

	int mWindNoChangeCount = 0;
	int mWindForceChangeCount = 2;

private:

	void HandleWind();

	float mWindDirection = 0;
};

