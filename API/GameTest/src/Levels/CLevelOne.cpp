#include "CLevelOne.h"


void CLevelOne::Start()
{	
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
	mObjectPool.SetPoolObject(pPlayer);
}

void CLevelOne::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		pPlayer->Destroy();
		pPlayer = nullptr;
	}

	if (pPlayer == nullptr) return;

	pPlayer->Update();
}

void CLevelOne::Render()
{
	if (pPlayer == nullptr) return;

	pPlayer->Render();
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	if (pPlayer == nullptr) return;
	pPlayer->Cleanup();
}

void CLevelOne::Shutdown()
{
}


bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}

