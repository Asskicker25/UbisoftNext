#pragma once

#include "../../Entities/CGameObject.h"
#include "EPowerUp.h"

class CPowerUpSpawner;

class CPowerUpPickup : public CGameObject
{
public:

	CPowerUpPickup(EPowerUp type);

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	EPowerUp mPowerUpType = NONE;

	Vector2 mSpeedRange = Vector2(50, 100);

	float mCurrentSpeed = 0;

	CPowerUpSpawner* mPowerUpSpawner;
};

