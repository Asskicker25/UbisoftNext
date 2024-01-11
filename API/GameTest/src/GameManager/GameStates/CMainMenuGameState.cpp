#include "CMainMenuGameState.h"

void CMainMenuGameState::Start()
{
	windowCenterX = APP_VIRTUAL_WIDTH / 2;
	windowCenterY = APP_VIRTUAL_HEIGHT / 2;
}

void CMainMenuGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		ChangeState(GAMEPLAY);
	}
}

void CMainMenuGameState::Render()
{
	App::Print(windowCenterX, windowCenterY + windowCenterY/2, " Game Name ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print(windowCenterX, windowCenterY - windowCenterY / 2,
		" Press Enter/Start To Begin ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);
}

void CMainMenuGameState::Cleanup()
{
}

void CMainMenuGameState::Pause()
{
}

void CMainMenuGameState::Resume()
{
}
