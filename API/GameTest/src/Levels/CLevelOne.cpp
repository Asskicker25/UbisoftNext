#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

#include "../World/CWorld.h"
#include "../Player/CPlayerManager.h"
#include "../Entities/CGameplayManager.h"
#include "../Tween/CTweenManager.h"

#include "../Environment/Wall/CWall.h"
#include "../Environment/Ground/CGround.h"
#include "../Player/Arc/CArcDot.h"

void CLevelOne::Start()
{

	CWorld::GetInstance().mOrigin = Vector2(-522, 0);

	CGameplayManager::GetInstance().OnTurnStart.Subscribe("Level_TurnStart", [this]()
		{
			HandleCameraMovement(true);
		});

	CPlayerManager::GetInstance().OnShoot.Subscribe("Level_Shoot", [this]()
		{
			HandleOnShoot();
		});


	CPlayerManager::GetInstance().Start();
	CGameplayManager::GetInstance().Start();

	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileFail.Subscribe("Player_Fail", [this]()
		{
			HandleCameraMovement(false);
		});

	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileSuccess.Subscribe("Player_Fail", [this]()
		{
			HandleCameraMovement(false);
		});

	CPlayerManager::GetInstance().OnPlayerDead.Subscribe("Level_Complete", [this]()
		{
			mIsLevelCompleted = true;
		});

	HandleEnvironmentCreations();
}

void CLevelOne::Update()
{
	HandleInput();
	HandleCameraFollow();
	CGameplayManager::GetInstance().Update();
	CPlayerManager::GetInstance().Update();
}

void CLevelOne::Render()
{
	std::string message = std::to_string(CWorld::GetInstance().mOrigin.x) + " , " + std::to_string(CWorld::GetInstance().mOrigin.y);

	App::Print(10, 110, message.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	CGameplayManager::GetInstance().Render();
	CPlayerManager::GetInstance().Render();
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	while (mEnvironmentObjects.size() != 0)
	{
		CGameObject* obj = mEnvironmentObjects[0];
		mEnvironmentObjects.erase(mEnvironmentObjects.begin());

		obj->Cleanup();
	}

	CPlayerManager::GetInstance().Cleanup();
	CGameplayManager::GetInstance().Cleanup();

	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("Level_TurnStart");
	CPlayerManager::GetInstance().OnShoot.UnSubscribe("Level_Shoot");
	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileFail.UnSubscribe("Player_Fail");
	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileSuccess.UnSubscribe("Player_Fail");
}

bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}

void CLevelOne::HandleInput()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}

	mCanCameraMove = App::GetController().CheckButton(XINPUT_GAMEPAD_A, false);

	if (!mCanCameraMove) return;

	mCameraMoveDir.x = App::GetController().GetLeftThumbStickX();
	mCameraMoveDir.y = App::GetController().GetLeftThumbStickY();

	mCameraMoveDir.Normalize();

	CWorld::GetInstance().mOrigin.x += mCameraMoveDir.x * 20;
	CWorld::GetInstance().mOrigin.y += mCameraMoveDir.y * 20;
}


void CLevelOne::HandleEnvironmentCreations()
{
	CWall* wall1 = new CWall();
	wall1->SetPosition(0, 600, true);
	CWall* wall2 = new CWall();
	wall2->SetPosition(0, 300, true);


	CArcDot* dot = new CArcDot();
	dot->SetPosition(0, 200, true);

	mEnvironmentObjects.push_back(wall1);
	mEnvironmentObjects.push_back(wall2);

	//Player 1 Side
	for (int i = -2; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CGround* ground1 = new CGround();

			if (j == 0 || i == -2)
			{
				ground1->pPhysicsShape = new CPhysicsShape(ground1, BOX);

			}
			ground1->SetPosition(-600 - i * ground1->pSprite->GetWidth(), 160 - j * ground1->pSprite->GetHeight(), true);

			mEnvironmentObjects.push_back(ground1);

		}
	}

	//Player 2 Side
	for (int i = -2; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CGround* ground1 = new CGround();

			if (j == 0 || i == -2)
			{
				ground1->pPhysicsShape = new CPhysicsShape(ground1, BOX);

			}
			ground1->SetPosition(600 + i * ground1->pSprite->GetWidth(), 160 - j * ground1->pSprite->GetHeight(), true);

			mEnvironmentObjects.push_back(ground1);

		}
	}


}

void CLevelOne::HandleCameraMovement(bool currentPlayer)
{

	float cameraValue;
	if (currentPlayer)
	{
		cameraValue = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -850 : -150;
	}
	else
	{
		cameraValue = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -150 : -850;
	}

	CTweenManager::GetInstance().AddFloatTween(CWorld::GetInstance().mOrigin.x, cameraValue, mCameraMoveTime,
		[](float value)
		{
			CWorld::GetInstance().mOrigin.x = value;
			CTweenManager::GetInstance();
		}
	);
}



void CLevelOne::HandleOnShoot()
{
	mCurrentProjectile = CPlayerManager::GetInstance().pProjectileFactory->GetCurrentProjectile();

	mOriginInitPos = CWorld::GetInstance().mOrigin;

	float x, y;

	mCurrentProjectile->pSprite->GetPosition(x, y);

	x -= mOriginInitPos.x;

	mProjectileLastPos = x;

	mCameraFollowProjectile = true;

}

void CLevelOne::HandleCameraFollow()
{

	if (!mCameraFollowProjectile) return;

	float x, y;

	mCurrentProjectile->pSprite->GetPosition(x, y);

	x -= mOriginInitPos.x;

	float mPosOffset = x - mProjectileLastPos;

	mProjectileLastPos = x;


	if (CGameplayManager::GetInstance().mCurrentTurn == 1)
	{
		if (x >= mWindowCenterX)
		{
			CWorld::GetInstance().mOrigin.x += mPosOffset;
		}
	}
	else
	{
		if (x <= mWindowCenterX)
		{
			CWorld::GetInstance().mOrigin.x += mPosOffset;
		}
	}

}