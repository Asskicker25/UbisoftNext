#pragma once

#include "CPlayerHealthIcon.h"
#include "CPowerUpUI.h"

class CPlayerHUD : public CGameObject
{
public:

	CPlayerHUD();

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;


	std::vector<CPlayerHealthIcon*> mPlayerOneHealth;
	std::vector<CPlayerHealthIcon*> mPlayerTwoHealth;

private:

	void HandleSpawningHearts();
	void HandlePlayerUI();
	void DrawPlayerInventory();

	void UpdatePlayerHealth(std::vector<CPlayerHealthIcon*>& mPlayerOneHealth);

	CPowerUpUI* mExplosiveUI = nullptr;
	CPowerUpUI* mMagnifyUI = nullptr;
	CPowerUpUI* mAmplifierUI = nullptr;
	CPowerUpUI* mNormalUI = nullptr;


	float mInventoryCenterX = 0;
	float mInventoryCenterY = 400;
	float mPosXFromScreen = 150;
	float mItemOffset = 60;
};

