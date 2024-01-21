#include "CControlsGameState.h"

CControlsGameState::CControlsGameState()
{
	
}

void CControlsGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;

	mBg = new CGameObject();
	mBg->pSprite = App::CreateSprite("Assets/Sprites/BG1.png", 1, 1);
	mBg->mIsUI = true;
	mBg->SetPosition(mWindowCenterX, mWindowCenterY, true);


	mExitUI = new CGameObject();
	mExitUI->pSprite = App::CreateSprite("Assets/Sprites/GO_TO_MENU.png", 1, 1);
	mExitUI->mIsUI = true;
	mExitUI->SetPosition(mWindowCenterX, mWindowCenterY - 200, true);
}

void CControlsGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		ChangeState(MAIN_MENU);
	}
}

void CControlsGameState::Render()
{
}

void CControlsGameState::Cleanup()
{
	mBg->Cleanup();
	mExitUI->Cleanup();
}

void CControlsGameState::Pause()
{
}

void CControlsGameState::Resume()
{
}
