#pragma once

#include "../../Entities/CGameObject.h"
#include "EPowerUp.h"

class CPowerUpSpawner;

class CPowerUpPickup : public CGameObject
{
public:

	CPowerUpPickup();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	virtual void CopyFromOther(CPowerUpPickup* other);


	void SetPowerUpType(EPowerUp type);

	EPowerUp mPowerUpType = NONE;

	Vector2 mSpeedRange = Vector2(50, 150);

	float mCurrentSpeed = 0;

	CPowerUpSpawner* mPowerUpSpawner = nullptr;

private:

	void HandleCollisionCheck();
};

