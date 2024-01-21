#include "CPlayerHUD.h"
#include "../CPlayerManager.h"
#include "../../Entities/CGameplayManager.h"
#include "../../EntityManager/CEntityManager.h"

CPlayerHUD::CPlayerHUD()
{

	HandleSpawningHearts();
	mExplosiveUI = new CPowerUpUI();
	mExplosiveUI->pSprite = App::CreateSprite("Assets/Sprites/Bomb_strip10.png", 10, 1);

	mMagnifyUI = new CPowerUpUI();
	mMagnifyUI->pSprite = App::CreateSprite("Assets/Sprites/Magnify_Scaled.png", 1, 1);

	mAmplifierUI = new CPowerUpUI();
	mAmplifierUI->pSprite = App::CreateSprite("Assets/Sprites/Fish_strip4.png", 4, 1);

	mNormalUI = new CPowerUpUI();
	mNormalUI->pSprite = App::CreateSprite("Assets/Sprites/Boot.png", 1, 1);
	mNormalUI->mCount->pSprite->SetScale(0.85f);
	mNormalUI->mCount->pSprite->SetAnimation(8);
	mNormalUI->mCount->pSprite->SetAngle(90 * PI / 180);


	CEntityManager::GetInstance().SortEntities();
}

void CPlayerHUD::Start()
{
	CGameObject::Start();

}

void CPlayerHUD::Update()
{
	DrawPlayerInventory();

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

	mAmplifierUI->Cleanup();
	mExplosiveUI->Cleanup();
	mMagnifyUI->Cleanup();
	mNormalUI->Cleanup();

	CPlayerManager::GetInstance().OnPlayerHit.UnSubscribe("UI_Update");

	CGameObject::Cleanup();
}

void CPlayerHUD::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CPlayerHUD::HandleSpawningHearts()
{

	CPlayer* playerOne = CPlayerManager::GetInstance().GetCurrentPlayer();
	CPlayer* playerTwo = CPlayerManager::GetInstance().GetOtherPlayer();

	float hudY = APP_VIRTUAL_HEIGHT - 50;
	float spacing = 10;

	for (int i = 0; i < playerOne->mMaxHealth; i++)
	{
		CPlayerHealthIcon* icon = new CPlayerHealthIcon();

		float posX = 50 + (i * (icon->pSprite->GetWidth() + spacing) * icon->pSprite->GetScale());

		icon->SetPosition(posX, hudY, true);

		mPlayerOneHealth.push_back(icon);
	}

	for (int i = 0; i < playerTwo->mMaxHealth; i++)
	{
		CPlayerHealthIcon* icon = new CPlayerHealthIcon();

		float posX = (APP_VIRTUAL_WIDTH - 50) - (i * (icon->pSprite->GetWidth() + spacing) * icon->pSprite->GetScale());

		icon->SetPosition(posX, hudY, true);
		mPlayerTwoHealth.push_back(icon);
	}

	CPlayerManager::GetInstance().OnPlayerHit.Subscribe("UI_Update", [this]()
		{
			HandlePlayerUI();
		});
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

void CPlayerHUD::DrawPlayerInventory()
{
	bool render = false;
	if (CGameplayManager::GetInstance().GetState() == PLAYER_AIM)
	{
		render = true;

		CPlayer* player = CPlayerManager::GetInstance().GetCurrentPlayer();

		mInventoryCenterX = CGameplayManager::GetInstance().mCurrentTurn == 1 ?
			mPosXFromScreen : APP_VIRTUAL_WIDTH - mPosXFromScreen;

		mExplosiveUI->SetPosition(mInventoryCenterX - mItemOffset, mInventoryCenterY, true);
		mAmplifierUI->SetPosition(mInventoryCenterX + mItemOffset, mInventoryCenterY, true);
		mMagnifyUI->SetPosition(mInventoryCenterX, mInventoryCenterY + mItemOffset, true);
		mNormalUI->SetPosition(mInventoryCenterX, mInventoryCenterY - mItemOffset, true);


		mExplosiveUI->SetCount(player->mExplosiveImpact.second);
		mAmplifierUI->SetCount(player->mDamageAmplifier.second);
		mMagnifyUI->SetCount(player->mMegaMagnify.second);
	}

	EPowerUp currentPowerUp = CPlayerManager::GetInstance().mCurrentPowerUp;

	mExplosiveUI->SetVisibility(render, currentPowerUp == EXPLOSIVE_IMPACT);
	mMagnifyUI->SetVisibility(render, currentPowerUp == MAGNIFY);
	mAmplifierUI->SetVisibility(render, currentPowerUp == DAMAGE_AMPLIFIER);
	mNormalUI->SetVisibility(render, currentPowerUp == NONE);

}

void CPlayerHUD::UpdatePlayerHealth(std::vector<CPlayerHealthIcon*>& playerHealth)
{
	CPlayer* player = CPlayerManager::GetInstance().GetOtherPlayer();
	for (int i = player->mMaxHealth - 1; i >= player->mTotalHealth; --i)
	{
		playerHealth[i]->pSprite->SetAnimation(1);
		playerHealth[i]->mOpacity = 0.4f;
	}
}
