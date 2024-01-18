#pragma once

#include "../LevelManager/CBaseLevel.h"

class CLevelTwo : public CBaseLevel
{
	// Inherited via CBaseLevel
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	bool IsLevelComplete() override;

private:
	bool mIsLevelCompleted = false;
};

