#pragma once

#include "../Entities/CGameObject.h"

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

	CPlayer(int controllerID = 0);

	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

	int mTotalHealth = 8;
	int mMaxHealth = 8;

	void ReduceHealth(int reduceAmount);
	

private:

	class Pimpl;
	Pimpl* pimpl;

};

