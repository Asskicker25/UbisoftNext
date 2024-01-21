#pragma once

#include "../LevelManager/CBaseLevel.h"
#include "../ObjectPooling/ObjectPool.h"

class CWall;

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
	void HandleOnShoot();
	void HandleEnvironmentCreations();
	void HandleCameraMovement(bool currentPlayer);
	void HandleCameraFollow();

	bool mIsLevelCompleted = false;
	bool mCanCameraMove = false;
	bool mCameraFollowProjectile = false;

	float mCameraMoveTime = 1;
	float mProjectileLastPos = 0;

	float mWindowCenterX = APP_VIRTUAL_WIDTH * 0.5f;
	float mWindowCenterY = APP_VIRTUAL_HEIGHT * 0.5f;

	Vector2 mCameraMoveDir;
	Vector2 mOriginInitPos;

	CGameObject* mCurrentProjectile = nullptr;

	CWall* wall1 = nullptr;
	CWall* wall2 = nullptr;

	std::vector<CGameObject* > mEnvironmentObjects;


};

