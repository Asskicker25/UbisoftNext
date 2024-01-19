#pragma once

#include "../App/app.h"
#include <string>
#include "../Game/Bullet/BulletFactory.h"

class CPlayer;

class CPlayerController
{

public:
	CPlayerController(CPlayer* player, int& controllerID);
	~CPlayerController();

	void Update();
	void Render();

	bool mIsEnabled = true;
	float mMoveSpeed = 0.05f;
	Vector2 mMoveDir = Vector2(0, 0);

private:

	int mFaceDir = 1;
	int mControllerID = 0;

	float mRayCastDistance = 40;

	bool mCanMove = true;

	std::string mAnimStateText = "IDLE_RIGHT";
	Vector2 mLastMoveDir = Vector2(0, 0);

	BulletFactory* bulletFactory = nullptr;

	CPlayer* pPlayer = nullptr;

	void HandleInput();
	void HandleRayCast();
	void HandleMove();
	void HandleCollision();
	void HandleRotation();
	void HandleAnimation();

	void ShootNormalBullet();

};

