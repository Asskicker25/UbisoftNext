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
	void HandleWallCreations();
	void HandleCameraMovement();

	bool mIsLevelCompleted = false;
	bool mCanCameraMove = false;

	float mCameraMoveTime = 2;

	Vector2 mCameraMoveDir;

	CWall* mWall1;

};

