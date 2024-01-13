#include "CLevelOne.h"

CGameObject* player;

void CLevelOne::Start()
{
	player = new CGameObject();
}

void CLevelOne::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}
}

void CLevelOne::Render()
{
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	delete player;
}

bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}
