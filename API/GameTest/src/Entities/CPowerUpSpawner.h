#pragma once

#include "CGameObject.h"
#include "../ObjectPooling/ObjectPool.h"
#include "../Player/PowerUps/CPowerUpPickup.h"

class CPowerUpSpawner : public CGameObject
{
public:

	CPowerUpSpawner();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	void RemovePowerUp(CGameObject* powerUp);

private:

	void SetRandomSpawnInterval();
	void HandleSpawnCalculate();
	void SpawnPickUp();

	float mSpawnCount = 1;
	float mTimeStep = 0;
	float mCurrentSpawnInterval = 0;

	float mSpawnYValue = 750;

	Vector2 mSpawnIntervalRange = Vector2(3, 8);
	Vector2 mSpawnXRange = Vector2(-230, 230);

	CGameObjectPool<CPowerUpPickup> mObjectPool;

};

