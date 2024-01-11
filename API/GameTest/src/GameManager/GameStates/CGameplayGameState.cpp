#include "CGameplayGameState.h"

void CGameplayGameState::Start()
{
}

void CGameplayGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		ChangeState(MAIN_MENU);
	}
}

void CGameplayGameState::Render()
{
	App::Print(10, 60, "GamePlay ", 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameplayGameState::Cleanup()
{
}
