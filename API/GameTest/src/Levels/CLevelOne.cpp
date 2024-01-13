#include "CLevelOne.h"

CGameObject* player;

void CLevelOne::Start()
{
	player = new CGameObject();

	player->sprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	player->sprite->SetPosition(400.0f, 400.0f);
	float speed = 1.0f / 15.0f;
	player->sprite->CreateAnimation(0, speed, { 0,1,2,3,4,5,6,7 });
	player->sprite->CreateAnimation(1, speed, { 8,9,10,11,12,13,14,15 });
	player->sprite->CreateAnimation(2, speed, { 16,17,18,19,20,21,22,23 });
	player->sprite->CreateAnimation(3, speed, { 24,25,26,27,28,29,30,31 });
	player->sprite->SetScale(1.0f);
}

void CLevelOne::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}

	player->Update();
}

void CLevelOne::Render()
{
	player->Render();
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	player->Cleanup();
}

void CLevelOne::Shutdown()
{
}


bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}

