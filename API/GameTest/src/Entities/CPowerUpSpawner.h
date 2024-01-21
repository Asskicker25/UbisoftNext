#pragma once

#include "CGameObject.h"


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

	Vector2 mSpawnIntervalRange = Vector2(2, 5);
	Vector2 mSpawnXRange = Vector2(-230, 230);

	std::vector<CGameObject*> mListOfPowerUps;

};

