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
	bool IsLevelComplete() override;


private:

	void HandleInput();

	bool mIsLevelCompleted = false;
	std::string mCollisionMessage = "";
	std::string mRaycastMessage = "";

	CPlayer* pPlayer = nullptr;
	CGameObject* mCircleCollider = nullptr;
	CGameObject* mBoxCollider = nullptr;
	CGameObject* mLineCollider = nullptr;

	CGameObjectPool mObjectPool;
};

