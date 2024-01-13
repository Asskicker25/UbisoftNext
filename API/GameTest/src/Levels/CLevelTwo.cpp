#include "CLevelTwo.h"

CGameObject* player2;

void CLevelTwo::Start()
{
	player2 = new CGameObject();
	player2->sprite = App::CreateSprite("Assets/Sprites/StrongMan.png",6,4);
	player2->sprite->SetPosition(400.0f, 400.0f);

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
