#include "CLevelOne.h"


void CLevelOne::Start()
{	
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
}

void CLevelOne::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}

	pPlayer->Update();
}

void CLevelOne::Render()
{
	pPlayer->Render();
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	pPlayer->Cleanup();
}

void CLevelOne::Shutdown()
{
}


bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}

