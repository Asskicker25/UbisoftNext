#include "CControlsGameState.h"
#include "../../EntityManager/CEntityManager.h"

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
	mBg->mOrder = -1;
	mBg->SetPosition(mWindowCenterX, mWindowCenterY, true);

	mControlsUI = new CGameObject();
	mControlsUI->pSprite = App::CreateSprite("Assets/Sprites/Controls.png", 1, 1);
	mControlsUI->mIsUI = true;
	mControlsUI->SetPosition(mWindowCenterX - 100, mWindowCenterY - 100, true);
	mControlsUI->pSprite->SetScale(0.8);

	mExitUI = new CGameObject();
	mExitUI->pSprite = App::CreateSprite("Assets/Sprites/GO_TO_MENU.png", 1, 1);
	mExitUI->mIsUI = true;
	mExitUI->SetPosition(mWindowCenterX, mWindowCenterY - 300, true);
	
	mPowerUps = new CGameObject();
	mPowerUps->pSprite = App::CreateSprite("Assets/Sprites/PowerUpControls.png", 1, 1);
	mPowerUps->mIsUI = true;
	mPowerUps->SetPosition(mWindowCenterX + 290, mWindowCenterY , true);

	CEntityManager::GetInstance().SortEntities();

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
	mPowerUps->Cleanup();
	mControlsUI->Cleanup();
}

void CControlsGameState::Pause()
{
}

void CControlsGameState::Resume()
{
}
