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

	while (mListOfPowerUps.size() != 0)
	{
		RemovePowerUp(mListOfPowerUps[0]);
	}

	CGameObject::Cleanup();
}

void CPowerUpSpawner::OnDestroy()
{
}

void CPowerUpSpawner::RemovePowerUp(CGameObject* powerUp)
{
	mListOfPowerUps.erase(std::remove(mListOfPowerUps.begin(), mListOfPowerUps.end(), powerUp), mListOfPowerUps.end());
	powerUp->mIsVisible = false;
	powerUp->mIsEnabled = false;
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
	CPowerUpPickup* powerUp = new CPowerUpPickup((EPowerUp) GetRandomIntNumber(1,3));

	powerUp->mPowerUpSpawner = this;

	powerUp->SetPosition(GetRandomFloatNumber(mSpawnXRange.x, mSpawnXRange.y), mSpawnYValue, true);

	mListOfPowerUps.push_back(powerUp);
		
	SetRandomSpawnInterval();
}
