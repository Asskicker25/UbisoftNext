#pragma once

#include "../Events/Events.h"
#include "../Player/UI/CPlayerHUD.h"
#include "../Environment/WindUI/CWindHUD.h"
#include "CPowerUpSpawner.h"

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

	CPlayerHUD* pPlayerHud = nullptr;
	CWindHUD* mWindHud = nullptr;
	CPowerUpSpawner* mPowerUpSpawner = nullptr;

	int mCurrentTurn = 1;

	int mWindStrength = 5;

	int mWindNoChangeCount = 0;
	int mWindForceChangeCount = 1;

private:

	void HandleWind();
	float mWindDirection = 0;
};

