#include "CCreditsGameState.h"

CCreditsGameState::CCreditsGameState()
{
	
}

void CCreditsGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;

	mBg = new CGameObject();
	mBg->pSprite = App::CreateSprite("Assets/Sprites/BG1.png", 1, 1);
	mBg->mIsUI = true;
	mBg->mOrder = -1;
	mBg->SetPosition(mWindowCenterX, mWindowCenterY, true);

	mExitUI = new CGameObject();
	mExitUI->pSprite = App::CreateSprite("Assets/Sprites/GO_TO_MENU.png", 1, 1);
	mExitUI->mIsUI = true;
	mExitUI->SetPosition(mWindowCenterX, mWindowCenterY - 250, true);

	mCreditsUI = new CGameObject();
	mCreditsUI->pSprite = App::CreateSprite("Assets/Sprites/Credits.png", 1, 1);
	mCreditsUI->mIsUI = true;
	mCreditsUI->SetPosition(mWindowCenterX, mWindowCenterY , true);
	
}

void CCreditsGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		ChangeState(MAIN_MENU);
	}
}

void CCreditsGameState::Render()
{
}

void CCreditsGameState::Cleanup()
{
	mExitUI->Cleanup();
	mBg->Cleanup();
	mCreditsUI->Cleanup();
}

void CCreditsGameState::Pause()
{
}

void CCreditsGameState::Resume()
{
}
