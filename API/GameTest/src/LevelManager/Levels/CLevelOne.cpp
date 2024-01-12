#include "CLevelOne.h"

void CLevelOne::Start()
{
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
}

bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}
