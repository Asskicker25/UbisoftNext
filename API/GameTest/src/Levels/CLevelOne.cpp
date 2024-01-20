#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

#include "../World/CWorld.h"
#include "../Player/CPlayerManager.h"
#include "../Entities/CGameplayManager.h"
#include "../Tween/CTweenManager.h"

#include "../Environment/Wall/CWall.h"

void CLevelOne::Start()
{

	CWorld::GetInstance().mOrigin = Vector2(-522, 0);

	CGameplayManager::GetInstance().OnTurnStart.Subscribe("Level_TurnStart", [this]()
		{
			HandleCameraMovement();
		});

	CPlayerManager::GetInstance().Start();
	CGameplayManager::GetInstance().Start();



	HandleWallCreations();
}

void CLevelOne::Update()
{
	HandleInput();
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

	mWall1->Cleanup();

	CPlayerManager::GetInstance().Cleanup();
	CGameplayManager::GetInstance().Cleanup();

	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("Level_TurnStart");
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

void CLevelOne::HandleWallCreations()
{
	mWall1 = new CWall();
	mWall1->SetPosition(0, 400, true);
}

void CLevelOne::HandleCameraMovement()
{
	float cameraValue = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -850 : -150;

	CTweenManager::GetInstance().AddFloatTween(CWorld::GetInstance().mOrigin.x, cameraValue, mCameraMoveTime,
		[](float value)
		{
			CWorld::GetInstance().mOrigin.x = value;
			CTweenManager::GetInstance();
		}
	);
}

