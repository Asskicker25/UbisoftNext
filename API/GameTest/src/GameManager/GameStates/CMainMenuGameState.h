#pragma once

#include "../CGameState.h"
#include "../../Entities/CGameObject.h"

class CMainMenuGameState : public CGameState
{

public:
	
	// Inherited via CGameState
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void Pause() override;
	void Resume() override;


private: 
	float mWindowCenterX = 0;
	float mWindowCenterY = 0;

	CGameObject* mBg = nullptr;
	CGameObject* mStartUI = nullptr;
	CGameObject* mControlsUI = nullptr;
	CGameObject* mCreditsUI = nullptr;


};

