#pragma once

#include "CPlayer.h"
#include "../Projectile/CProjectileFactory.h"
#include "../Events/Events.h"
#include "Arc/CArcRenderer.h"

#include "PowerUps/EPowerUp.h"

class CPlayerManager 
{
public:

	CPlayerManager();
	~CPlayerManager();

	static CPlayerManager& GetInstance();

	void Start();
	void Update();
	void Render();
	void Cleanup();

	CPlayer* GetCurrentPlayer();
	CPlayer* GetOtherPlayer();

	bool GetPreviousArc(std::vector<Vector2>& prevArc);

	CPlayer* pPlayer_One = nullptr;
	CPlayer* pPlayer_Two = nullptr;

	CProjectileFactory* pProjectileFactory = nullptr;

	CArcRenderer* mCurrentArc = nullptr;
	CArcRenderer* mPrevArc = nullptr;

	EPowerUp mCurrentPowerUp = NONE;
	EProjectileType mProjectileType = NORMAL;

	CBasePowerUp* pCurrentPowerUp = nullptr;

	Vector2 mAimDirection;

	std::vector<Vector2> mCurrentArcPositions;

	float mPlayerOffset = 600;

	CEvents OnShoot;
	CEvents OnPlayerHit;
	CEvents OnPlayerDead;

private:

	void HandleTurnStart();
	void HandleInput();
	void HandleShoot();
	void HandleAim();
	void HandlePlayerDead();
	void HandlePowerUpInput();
	bool SwitchPowerUp(EPowerUp type);
	void PowerUpUsed();


	void HandleProjectileHit(bool success);

	void RenderArc();

	std::vector<Vector2> mPlayerOnePrevArc;
	std::vector<Vector2> mPlayerTwoPrevArc;

	float mThrowingDuration = 0.1f;
	float mLevelEndDuration = 2.0f;
	float mProjectHitAnimDuration = 1.5f;
	float mArcLength = 0.3f;	

	float mAimLerpSpeed = 1;

	float mCurrentAngle = 0;
	float mAimMinAngle = 10.0f;
	float mAimMaxAngle = 50.0f;

	float mForce = 117;

	int mArcResolution = 50;
};

