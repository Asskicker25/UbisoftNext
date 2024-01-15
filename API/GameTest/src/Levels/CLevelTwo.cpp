#include "CLevelTwo.h"

CGameObject* player2;

void CLevelTwo::Start()
{
	player2 = new CGameObject();
	player2->sprite = App::CreateSprite("Assets/Sprites/Batman_01_strip6.png",6,1);
	player2->sprite->SetPosition(400.0f, 400.0f);
	float speed = 1.0f / 3.0f;
	player2->sprite->CreateAnimation(0, speed, { 0 });
	player2->sprite->CreateAnimation(1, speed, { 1,2,3,4,5 });
	/*player2->sprite->CreateAnimation(2, speed, { 16,17,18,19,20,21,22,23 });
	player2->sprite->CreateAnimation(3, speed, { 24,25,26,27,28,29,30,31 });*/

	player2->sprite->SetAnimation(1);

}

void CLevelTwo::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}

	player2->Update();
}

void CLevelTwo::Render()
{
	player2->Render();
}

void CLevelTwo::Cleanup()
{
	mIsLevelCompleted = false;

	player2->Cleanup();
}

void CLevelTwo::Shutdown()
{
}

bool CLevelTwo::IsLevelComplete()
{
    return mIsLevelCompleted;
}
