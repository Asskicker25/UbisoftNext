#pragma once

#include "../App/app.h"
#include <string>

class CPlayerController
{

public:
	CPlayerController(CSimpleSprite* sprite);
	~CPlayerController();

	void Update();
	void Render();

	bool mIsEnabled = true;
	float mMoveSpeed = 0.05f;
	Vector2 mMoveDir = Vector2(0, 0);

private:

	int mFaceDir = 1;
	std::string mAnimStateText = "IDLE_RIGHT";
	Vector2 mLastMoveDir = Vector2(0, 0);

	CSimpleSprite* pSprite = nullptr;

	void HandleInput();
	void HandleMove();
	void HandleRotation();
	void HandleAnimation();

};

