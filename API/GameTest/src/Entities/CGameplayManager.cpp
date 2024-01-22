#include "CGameplayManager.h"
#include "../Player/CPlayerManager.h"
#include "../Utilities/Random.h"
#include "CNumberUI.h"
#include "../Tween/CTweenManager.h"

CGameplayManager::CGameplayManager()
{
}

CGameplayManager& CGameplayManager::GetInstance()
{
	static CGameplayManager instance;
	return instance;
}

void CGameplayManager::Start()
{
	mCurrentTurn = 2;
	mCleanedUp = false;
	mCurrentRound = 0;

	pPlayerHud = new CPlayerHUD();
	mWindHud = new CWindHUD();
	mPowerUpSpawner = new CPowerUpSpawner();
	mNightManager = new CNightManager();

	mRoundUI = new CGameObject();
	mRoundUI->pSprite = App::CreateSprite("Assets/Sprites/Round.png", 1, 1);
	mRoundUI->mIsUI = true;
	mRoundUI->SetPosition(APP_VIRTUAL_WIDTH / 2 - 10, APP_VIRTUAL_HEIGHT - 150, true);
	mRoundUI->pSprite->SetScale(0.2f);

	mRoundCountUI = new CNumberUI();
	mRoundCountUI->SetPosition(mRoundCountUIX - 10, APP_VIRTUAL_HEIGHT - 149, true);
	mRoundCountUI->pSprite->SetScale(0.72);

	mNightTextUI = new CGameObject();
	mNightTextUI->pSprite = App::CreateSprite("Assets/Sprites/sprite5_Darkness_Approaches_In.png", 1, 1);
	mNightTextUI->mIsUI = true;
	mNightTextUI->SetPosition(130, APP_VIRTUAL_HEIGHT - 120, true);
	mNightTextUI->pSprite->SetScale(0.4f);

	mNightCountUI = new CNumberUI();
	mNightCountUI->SetPosition(130 + 110, APP_VIRTUAL_HEIGHT - 115, true);
	mNightCountUI->pSprite->SetScale(0.72);

	mPlayerTurnUI = new CGameObject();
	mPlayerTurnUI->mIsUI = true;
	mPlayerTurnUI->pSprite = App::CreateSprite("Assets/Sprites/PlayerTurn_strip2.png", 2, 1);
	mPlayerTurnUI->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT -250, true);
	mPlayerTurnUI->pSprite->CreateAnimation(0, 1, { 0 });
	mPlayerTurnUI->pSprite->CreateAnimation(1, 1, { 1 });
	mPlayerTurnUI->pSprite->SetAnimation(0);
	mPlayerTurnUI->pSprite->SetScale(0);
	mPlayerTurnUI->mOpacity = 0.85f;

	SwitchTurn();
	HandleRoundSwitch();
}

void CGameplayManager::Update()
{
}

void CGameplayManager::Render()
{
	/*std::string wallSwitchMessage = "Wall Switch in : " + std::to_string(mCurrentWallSwitchRound - mCurrentRound);

	App::Print(500, 500, wallSwitchMessage.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	std::string nightMessage = "Night in : " + std::to_string(mCurrentNightSwitchRound - mCurrentRound);

	App::Print(500, 450, nightMessage.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);*/
}

void CGameplayManager::Cleanup()
{
	pPlayerHud->Cleanup();
	mWindHud->Cleanup();
	mPowerUpSpawner->Cleanup();
	mNightManager->Cleanup();

	mRoundCountUI->Cleanup();
	mRoundUI->Cleanup();

	mNightTextUI->Cleanup();
	mNightCountUI->Cleanup();

	mPlayerTurnUI->Cleanup();

	mCurrentNightSwitchRound = 0;
	mCurrentWallSwitchRound = 0;

	mCleanedUp = true;
}

void CGameplayManager::SwitchTurn()
{
	if (mCleanedUp) return;

	mCurrentTurn = mCurrentTurn == 1 ? 2 : 1;

	HandleRoundIncrement();
	HandleWind();
	HandleTurnText();

	mWindHud->SetDirection(mWindDirection);

	SetState(PLAYER_AIM);
	OnTurnStart.Invoke();
}

EGameplayState CGameplayManager::GetState()
{
	return mCurrentState;
}

void CGameplayManager::SetState(EGameplayState state)
{
	this->mCurrentState = state;
}

float CGameplayManager::GetWindForce()
{
	//return 1;
	return (mCurrentTurn == 1 ? 1 : -1) * mWindDirection * mWindStrength;
}

void CGameplayManager::HandleWind()
{
	if (mWindNoChangeCount < mWindForceChangeCount)
	{
		int random = GetRandomIntNumber(0, 1);

		if (random == 0)
		{
			mWindNoChangeCount++;

			if (mWindDirection == 0) { mWindDirection = 0.1f; }
			return;
		}
	}

	mWindDirection = GetRandomFloatNumber(-1.0f, 1.0f);
	mWindNoChangeCount = 0;
}

void CGameplayManager::HandleRoundSwitch()
{
	mNightManager->DeActivate();

	mNightCountUI->SetNumber(mCurrentNightSwitchRound - mCurrentRound);

	if (mCurrentRound >= mCurrentWallSwitchRound)
	{
		if (mCurrentWallSwitchRound != 0)
		{
			OnWallSwitch.Invoke();
		}
		CalculateRandomRound(mCurrentWallSwitchRound, mWallSwitchRoundRange.x, mWallSwitchRoundRange.y);
	}

	if (mCurrentRound >= mCurrentNightSwitchRound)
	{
		if (mCurrentNightSwitchRound != 0)
		{
			mNightManager->Activate();
			//mNightManager.
		}
		CalculateRandomRound(mCurrentNightSwitchRound, mNightSwitchRoundRange.x, mNightSwitchRoundRange.y);
	}



}

void CGameplayManager::HandleRoundIncrement()
{

	if (mCurrentTurn == 1)
	{
		++mCurrentRound;

		mRoundCountUI->SetNumber(mCurrentRound);

		HandleRoundSwitch();
	}
}

void CGameplayManager::HandleTurnText()
{
	mPlayerTurnUI->pSprite->SetAnimation(mCurrentTurn == 1 ? 0 : 1);

	CTweenManager::GetInstance().AddFloatTween(0, 0.6, 1, [this](float value)
		{
			mPlayerTurnUI->pSprite->SetScale(value);
			
		});

	CTimerEventsHandler::GetInstance().AddDelay([this]()
		{
			CTweenManager::GetInstance().AddFloatTween(0.6, 0, 1, [this](float value)
				{
					mPlayerTurnUI->pSprite->SetScale(value);
				});
		}, 2);


}

void CGameplayManager::CalculateRandomRound(int& mRandomRound, int rangeX, int rangeY)
{
	mRandomRound = GetRandomIntNumber(rangeX, rangeY);

	mRandomRound += mCurrentRound;
}

