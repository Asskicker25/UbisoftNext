#pragma once

#include "../CGameState.h"

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

};

