#include "CLevelCompleteGameState.h"
#include "../../LevelManager/CLevelManager.h"
#include "../../EntityManager/CEntityManager.h"


// Initializes the level complete state.
void CLevelCompleteGameState::Start()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;
	
	mBg = new CGameObject();
	mBg->pSprite = App::CreateSprite("Assets/Sprites/BG1.png", 1, 1);
	mBg->mIsUI = true;
	mBg->mOrder = -1;
	mBg->SetPosition(mWindowCenterX, mWindowCenterY, true);


	mExitUI = new CGameObject();
	mExitUI->pSprite = App::CreateSprite("Assets/Sprites/LevelCompleteMainMenu.png", 1, 1);
	mExitUI->mIsUI = true;
	mExitUI->SetPosition(mWindowCenterX, mWindowCenterY - 200, true);

	mHeader = new CGameObject();
	mHeader->pSprite = App::CreateSprite("Assets/Sprites/GameOver.png", 1, 1);
	mHeader->mIsUI = true;
	mHeader->SetPosition(mWindowCenterX, mWindowCenterY + 100, true);
	mHeader->pSprite->SetScale(3.0f);


	mPlayerWonIndex = CLevelManager::GetInstance().mPlayerWon;
	
	mPlayerWon = new CGameObject();
	mPlayerWon->pSprite = App::CreateSprite("Assets/Sprites/PlayerWon_strip2.png", 2, 1);
	mPlayerWon->mIsUI = true;

	mPlayerWon->pSprite->CreateAnimation(1, 1, { 0 });
	mPlayerWon->pSprite->CreateAnimation(2, 1, { 1 });

	mPlayerWon->SetPosition(mWindowCenterX, mWindowCenterY - 50, true);
	mPlayerWon->pSprite->SetScale(0.8f);

	mPlayerWon->pSprite->SetAnimation(mPlayerWonIndex);

	CEntityManager::GetInstance().SortEntities();

}

// Handles user input to transition to the next level or return to the main menu.
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

// Displays the level completion message and prompt for the next level.
void CLevelCompleteGameState::Render()
{
	/*App::Print(mWindowCenterX, mWindowCenterY + mWindowCenterY / 2, "Level Complete ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(mWindowCenterX, mWindowCenterY, "Press Enter/Start to Next Level ", 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);*/

	//App::Print(mWindowCenterX, mWindowCenterY,  std::to_string(mPlayerWonIndex).c_str(), 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);
}

void CLevelCompleteGameState::Cleanup()
{
	mBg->Cleanup();
	mExitUI->Cleanup();
	mHeader->Cleanup();
	mPlayerWon->Cleanup();
}

void CLevelCompleteGameState::Pause()
{
}

void CLevelCompleteGameState::Resume()
{
}
