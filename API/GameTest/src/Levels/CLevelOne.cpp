#include "CLevelOne.h"


void CLevelOne::Start()
{	
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
	mObjectPool.SetPoolObject(pPlayer);
}

void CLevelOne::Update()
{
	HandleInput();

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
	mObjectPool.Cleanup();

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

void CLevelOne::HandleInput()
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

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		mObjectPool.DestroyObject( mObjectPool.SpawnObject(), 3.0f);
	}
}

