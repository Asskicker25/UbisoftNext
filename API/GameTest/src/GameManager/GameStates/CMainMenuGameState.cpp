#include "CMainMenuGameState.h"
#include "../../LevelManager/CLevelManager.h"


// Initializes the main menu state.
void CMainMenuGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;
}

// Handles user input to transition to the gameplay state.
void CMainMenuGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		CLevelManager::GetInstance().Start();

		ChangeState(GAMEPLAY);
	}
}

// Displays the main menu content on the screen.
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
