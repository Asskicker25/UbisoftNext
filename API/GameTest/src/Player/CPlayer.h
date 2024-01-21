#pragma once

#include "../Entities/CGameObject.h"

#include "PowerUps/CBasePowerUp.h"
#include "PowerUps/EPowerUp.h"

enum EPlayerAnimState
{
	IDLE = 0,
	AIM = 1,
	THROW = 2,
	TAUNT = 3,
	HIT_ONE = 4,
	HIT_TWO = 5,
	DEATH = 6
};

class CPlayer : public CGameObject
{
public:

	CPlayer(const std::string& spritePath, int controllerID = 0);

	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

	int mTotalHealth = 0;
	int mMaxHealth = 5;

	void ReduceHealth(int reduceAmount);
	void AddPowerUp(EPowerUp type);

	bool IsPlayerDead();
	
	std::pair<CBasePowerUp*, int> mMegaMagnify;
	std::pair<CBasePowerUp*, int> mDamageAmplifier;
	std::pair<CBasePowerUp*, int> mExplosiveImpact;

private:

	class Pimpl;
	Pimpl* pimpl;

};

