#pragma once

#include "CPlayer.h"
#include "../Projectile/CProjectileFactory.h"
#include "../Events/Events.h"


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

	float mPlayerOffset = 600;

	Vector2 mAimDirection;

	std::vector<Vector2> mCurrentArcPositions;

	CEvents OnShoot;
	CEvents OnPlayerHit;
	CEvents OnPlayerDead;

private:

	void HandleTurnStart();
	void HandleInput();
	void HandleShoot();
	void HandleAim();
	void HandlePlayerDead();

	void HandleProjectileHit(bool success);

	void RenderArc();

	std::vector<Vector2> mPlayerOnePrevArc;
	std::vector<Vector2> mPlayerTwoPrevArc;

	float mThrowingDuration = 0.1f;
	float mLevelEndDuration = 2.0f;
	float mProjectHitAnimDuration = 1.5f;
	float mArcLength = 0.3f;	

	float mCurrentAngle = 0;
	float mAimMinAngle = 15.0f;
	float mAimMaxAngle = 50.0f;

	float mForce = 117;

	int mArcResolution = 10;
};

