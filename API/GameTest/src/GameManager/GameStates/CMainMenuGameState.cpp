#include "CMainMenuGameState.h"
#include "../../LevelManager/CLevelManager.h"


// Initializes the main menu state.
void CMainMenuGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;

	mBg = new CGameObject();
	mBg->pSprite = App::CreateSprite("Assets/Sprites/BG1.png",1,1);
	mBg->mIsUI = true;
	mBg->SetPosition(mWindowCenterX, mWindowCenterY, true);


	mStartUI = new CGameObject();
	mStartUI->pSprite = App::CreateSprite("Assets/Sprites/Press_Start.png", 1, 1);
	mStartUI->mIsUI = true;
	mStartUI->SetPosition(mWindowCenterX, mWindowCenterY - 100, true);
	
	mControlsUI = new CGameObject();
	mControlsUI->pSprite = App::CreateSprite("Assets/Sprites/ViewControls.png", 1, 1);
	mControlsUI->mIsUI = true;
	mControlsUI->SetPosition(mWindowCenterX, mWindowCenterY - 150, true);
	
	mCreditsUI = new CGameObject();
	mCreditsUI->pSprite = App::CreateSprite("Assets/Sprites/ViewCredits.png", 1, 1);
	mCreditsUI->mIsUI = true;
	mCreditsUI->SetPosition(mWindowCenterX, mWindowCenterY - 200, true);



}

// Handles user input to transition to the gameplay state.
void CMainMenuGameState::Update()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		CLevelManager::GetInstance().Start();

		ChangeState(GAMEPLAY);
	}
	
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		ChangeState(CONTROLS);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		ChangeState(CREDITS);
	}
}

// Displays the main menu content on the screen.
void CMainMenuGameState::Render()
{
}

void CMainMenuGameState::Cleanup()
{
	mBg->Cleanup();
	mStartUI->Cleanup();
	mControlsUI->Cleanup();
	mCreditsUI->Cleanup();
}

void CMainMenuGameState::Pause()
{
}

void CMainMenuGameState::Resume()
{
}
