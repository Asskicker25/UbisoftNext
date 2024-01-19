#pragma once

#include "CPlayer.h"


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

	CPlayer* pPlayer_One = nullptr;
	CPlayer* pPlayer_Two = nullptr;

	float mPlayerOffset = 600;

	Vector2 mAimDirection;

	std::vector<Vector2> mCurrentArcPositions;

private:

	void HandleTurnStart();
	void HandleInput();
	void HandleShoot();
	void HandleAim();

	void RenderArc();

	float mThrowingDuration = 0.5f;
	float mArcLength = 1.0f;	

	float mCurrentAngle = 0;
	float mAimMinAngle = 15.0f;
	float mAimMaxAngle = 50.0f;

	float mForce = 117;

	int mArcResolution = 10;
};

