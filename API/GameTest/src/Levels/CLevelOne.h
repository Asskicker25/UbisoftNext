#pragma once

#include "../LevelManager/CBaseLevel.h"
#include "../Player/CPlayer.h"
#include "../ObjectPooling/ObjectPool.h"

class CLevelOne : public CBaseLevel
{

public:

	// Inherited via CBaseLevel
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void Shutdown() override;
	bool IsLevelComplete() override;


private:
	bool mIsLevelCompleted = false;

	CPlayer* pPlayer = nullptr;
	CGameObjectPool mObjectPool;
};

