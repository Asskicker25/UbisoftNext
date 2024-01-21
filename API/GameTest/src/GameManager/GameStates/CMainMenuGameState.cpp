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
	mBg->Cleanup();
	mStartUI->Cleanup();
}

void CMainMenuGameState::Pause()
{
}

void CMainMenuGameState::Resume()
{
}
