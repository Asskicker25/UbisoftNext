#include "CLevelCompleteGameState.h"
#include "../../LevelManager/CLevelManager.h"


void CLevelCompleteGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;
}

void CLevelCompleteGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		if (CLevelManager::GetInstance().NextLevel())
		{
			ChangeState(GAMEPLAY);
		}
		else
		{
			ChangeState(MAIN_MENU);
		}
	}
}

void CLevelCompleteGameState::Render()
{
	App::Print(mWindowCenterX, mWindowCenterY + mWindowCenterY / 2, "Level Complete ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(mWindowCenterX, mWindowCenterY, "Press Enter/Start to Next Level ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);
}

void CLevelCompleteGameState::Cleanup()
{
}

void CLevelCompleteGameState::Pause()
{
}

void CLevelCompleteGameState::Resume()
{
}
