#include "CPlayerHUD.h"
#include "../CPlayerManager.h"
#include "../../Entities/CGameplayManager.h"

void CPlayerHUD::Start()
{
	CGameObject::Start();

	CPlayer* playerOne = CPlayerManager::GetInstance().GetCurrentPlayer();
	CPlayer* playerTwo = CPlayerManager::GetInstance().GetOtherPlayer();

	float hudY = APP_VIRTUAL_HEIGHT - 50; 
	float spacing = -75;

	for (int i = 0; i < playerOne->mMaxHealth; i++)
	{
		CPlayerHealthIcon* icon = new CPlayerHealthIcon();

		float posX = 50 + (i * (icon->pSprite->GetWidth() + spacing) * icon->pSprite->GetScale() );

		icon->SetPosition(posX,hudY, true);

		mPlayerOneHealth.push_back(icon);
	}

	for (int i = 0; i < playerTwo->mMaxHealth; i++)
	{
		CPlayerHealthIcon* icon = new CPlayerHealthIcon();

		float posX = (APP_VIRTUAL_WIDTH -  50 ) - (i * (icon->pSprite->GetWidth() + spacing) * icon->pSprite->GetScale());

		icon->SetPosition(posX, hudY, true);
		mPlayerTwoHealth.push_back(icon);
	}

	CPlayerManager::GetInstance().OnPlayerHit.Subscribe("UI_Update", [this]()
		{
			HandlePlayerUI();
		});

}

void CPlayerHUD::Update()
{
	CGameObject::Update();
}

void CPlayerHUD::Render()
{
	CGameObject::Render();
}

void CPlayerHUD::Cleanup()
{

	while (mPlayerOneHealth.size() != 0)
	{
		CPlayerHealthIcon* icon = mPlayerOneHealth[0];

		mPlayerOneHealth.erase(std::remove(mPlayerOneHealth.begin(), mPlayerOneHealth.end(), icon), mPlayerOneHealth.end());

		icon->Cleanup();
	}

	while (mPlayerTwoHealth.size() != 0)
	{
		CPlayerHealthIcon* icon = mPlayerTwoHealth[0];

		mPlayerTwoHealth.erase(std::remove(mPlayerTwoHealth.begin(), mPlayerTwoHealth.end(), icon), mPlayerTwoHealth.end());

		icon->Cleanup();
	}

	CPlayerManager::GetInstance().OnPlayerHit.UnSubscribe("UI_Update");

	CGameObject::Cleanup();
}

void CPlayerHUD::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CPlayerHUD::HandlePlayerUI()
{
	if (CGameplayManager::GetInstance().mCurrentTurn == 1)
	{
		UpdatePlayerHealth(mPlayerTwoHealth);
	}
	else
	{
		UpdatePlayerHealth(mPlayerOneHealth);
	}
}

void CPlayerHUD::UpdatePlayerHealth(std::vector<CPlayerHealthIcon*>& playerHealth)
{
	CPlayer* player = CPlayerManager::GetInstance().GetOtherPlayer();
	for (int i = player->mMaxHealth - 1; i >= player->mTotalHealth; --i)
	{
		playerHealth[i]->mIsVisible = false;
	}
}
