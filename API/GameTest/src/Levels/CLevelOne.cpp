#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

#include "../World/CWorld.h"

void CLevelOne::Start()
{
	pPlayer1 = new CPlayer(0);
	pPlayer1->pSprite->SetPosition(400, 400);
	pPlayer1->mName = "Player 1";
	pPlayer1->mTag = "Player";

	pPlayer2 = new CPlayer(1);
	pPlayer2->pSprite->SetPosition(600, 400);
	pPlayer2->mName = "Player 2";
	pPlayer2->mTag = "Untagged";

}

void CLevelOne::Update()
{
	HandleInput();
}

void CLevelOne::Render()
{
	std::string message = std::to_string(mCameraMoveDir.x) + " , " + std::to_string(mCameraMoveDir.y);
	App::Print(600, 60, message.c_str(), 0, 1, 0);
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	if (pPlayer1 == nullptr) return;

	pPlayer1->Cleanup();
	pPlayer2->Cleanup();
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

	mCameraMoveDir.x = App::GetController().GetRightThumbStickX();
	mCameraMoveDir.y = App::GetController().GetRightThumbStickX();

	mCameraMoveDir.Normalize();
	
	CWorld::GetInstance().mOrigin.x += mCameraMoveDir.x * 20;
	CWorld::GetInstance().mOrigin.y += mCameraMoveDir.y * 20;
}

