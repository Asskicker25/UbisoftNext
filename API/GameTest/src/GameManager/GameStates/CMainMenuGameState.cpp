#include "CMainMenuGameState.h"
#include "../../LevelManager/CLevelManager.h"

void CMainMenuGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;
}

void CMainMenuGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		CLevelManager::GetInstance().Start();

		ChangeState(GAMEPLAY);
	}
}

void CMainMenuGameState::Render()
{
	App::Print(mWindowCenterX, mWindowCenterY + mWindowCenterY /2, " Game Name ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print(mWindowCenterX, mWindowCenterY - mWindowCenterY / 2,
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
