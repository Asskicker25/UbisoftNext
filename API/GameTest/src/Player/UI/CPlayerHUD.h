#pragma once

#include "CPlayerHealthIcon.h"

class CPlayerHUD : public CGameObject
{
public:

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

	std::vector<CPlayerHealthIcon*> mPlayerOneHealth;
	std::vector<CPlayerHealthIcon*> mPlayerTwoHealth;

private:

	void HandlePlayerUI();
	void UpdatePlayerHealth(std::vector<CPlayerHealthIcon*>& mPlayerOneHealth);
};

