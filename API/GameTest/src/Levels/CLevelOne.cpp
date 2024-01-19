#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

void CLevelOne::Start()
{
	pPlayer1 = new CPlayer(0);
	pPlayer1->pSprite->SetPosition(400, 400);

	pPlayer2 = new CPlayer(1);
	pPlayer2->pSprite->SetPosition(600, 400);

}

void CLevelOne::Update()
{
	HandleInput();
}

void CLevelOne::Render()
{

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
	
}

