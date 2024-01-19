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

private:

	void HandleTurnStart();
	void HandleInput();

	float mThrowingDuration = 1.0f;
};

