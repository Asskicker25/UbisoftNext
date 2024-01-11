#pragma once

#include "../CGameState.h"

class CGameplayGameState : public CGameState
{

public:

	~CGameplayGameState();

	// Inherited via CGameState
	void Start() override;
	void Update() override;
	void Render() override;

	void Cleanup() override;
	void Pause() override;
	void Resume() override;

};

