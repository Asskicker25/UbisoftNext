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

};

