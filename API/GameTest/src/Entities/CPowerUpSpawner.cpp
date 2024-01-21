#include "CPowerUpSpawner.h"
#include "../Player/PowerUps/CPowerUpPickup.h"
#include "../Utilities/Random.h"
#include "../Timer/CTimer.h"

CPowerUpSpawner::CPowerUpSpawner() : CGameObject()
{
}

void CPowerUpSpawner::Start()
{
	CGameObject::Start();

	/*CPowerUpPickup* powerUp = new CPowerUpPickup((EPowerUp)GetRandomIntNumber(1, 3));
	CPowerUpPickup* powerUp1 = new CPowerUpPickup((EPowerUp)GetRandomIntNumber(1, 3));

	powerUp->SetPosition(mSpawnXRange.x, mSpawnYValue, true);
	powerUp1->SetPosition(mSpawnXRange.y, mSpawnYValue, true);*/

	CPowerUpPickup* base = new CPowerUpPickup();
	base->mIsEnabled = false;
	base->mIsVisible = false;
	base->mPowerUpSpawner = this;
	mObjectPool.SetPoolObject(base);


	SetRandomSpawnInterval();
}

void CPowerUpSpawner::Update()
{
	HandleSpawnCalculate();

	CGameObject::Update();
}

void CPowerUpSpawner::Render()
{
	CGameObject::Render();
}

void CPowerUpSpawner::Cleanup()
{
	mObjectPool.Cleanup();

	CGameObject::Cleanup();
}

void CPowerUpSpawner::OnDestroy()
{
}

void CPowerUpSpawner::RemovePowerUp(CGameObject* powerUp)
{
	mObjectPool.DestroyObject((CPowerUpPickup*)powerUp);
	//powerUp->Cleanup();
}

void CPowerUpSpawner::SetRandomSpawnInterval()
{
	mCurrentSpawnInterval = GetRandomFloatNumber(mSpawnIntervalRange.x, mSpawnIntervalRange.y);
	mTimeStep = 0;
}

void CPowerUpSpawner::HandleSpawnCalculate()
{
	mTimeStep += CTimer::GetInstance().mDeltaTime;

	if (mTimeStep >= mCurrentSpawnInterval)
	{
		SpawnPickUp();
	}
}

void CPowerUpSpawner::SpawnPickUp()
{
	CPowerUpPickup* powerUp = mObjectPool.SpawnObject();
	powerUp->SetPowerUpType((EPowerUp) GetRandomIntNumber(1,3));

	powerUp->SetPosition(GetRandomFloatNumber(mSpawnXRange.x, mSpawnXRange.y), mSpawnYValue, true);

	SetRandomSpawnInterval();
}
