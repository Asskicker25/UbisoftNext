#include "CMainMenuGameState.h"

void CMainMenuGameState::Start()
{
}

void CMainMenuGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		ChangeState(GAMEPLAY);
	}
}

void CMainMenuGameState::Render()
{
	App::Print(10, 60, "Main Menu ", 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CMainMenuGameState::Cleanup()
{
}
