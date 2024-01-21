#pragma once

#include "../CGameState.h"
#include "../../Entities/CGameObject.h"

class CLevelCompleteGameState : public CGameState
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
	CGameObject* mExitUI = nullptr;
	CGameObject* mHeader = nullptr;

};

