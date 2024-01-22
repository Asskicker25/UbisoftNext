#pragma once

#include "../Events/Events.h"
#include "../Player/UI/CPlayerHUD.h"
#include "../Environment/WindUI/CWindHUD.h"
#include "CPowerUpSpawner.h"
#include "CNightManager.h"
#include "CNumberUI.h"

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
	CEvents OnWallSwitch;

	EGameplayState mCurrentState = PLAYER_AIM;

	CPlayerHUD* pPlayerHud = nullptr;
	CWindHUD* mWindHud = nullptr;
	CPowerUpSpawner* mPowerUpSpawner = nullptr;
	CNightManager* mNightManager = nullptr;

	CGameObject* mRoundUI = nullptr;
	CNumberUI* mRoundCountUI = nullptr;
	
	CGameObject* mNightTextUI = nullptr;
	CNumberUI* mNightCountUI = nullptr;

	CGameObject* mPlayerTurnUI = nullptr;

	Vector2 mWallSwitchRoundRange = Vector2(2, 5);
	Vector2 mNightSwitchRoundRange = Vector2(3, 5);


	float mRoundCountUIX = 550;

	int mCurrentTurn = 1;
	int mCurrentRound = 0;
	int mWindStrength = 5;
	int mWindNoChangeCount = 0;
	int mWindForceChangeCount = 1;
	int mCurrentWallSwitchRound = 0;
	int mCurrentNightSwitchRound = 0;
	
	bool mCleanedUp = false;

private:

	void HandleWind();
	void HandleRoundSwitch();
	void HandleRoundIncrement();
	void HandleTurnText();

	void CalculateRandomRound(int& mRandomRound, int rangeX, int rangeY);

	float mWindDirection = 0;
};

