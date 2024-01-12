#pragma once

#include "../CBaseLevel.h"

class CLevelOne : public CBaseLevel
{

public:

	// Inherited via CBaseLevel
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	bool IsLevelComplete() override;

private:
	bool mIsLevelCompleted = false;
};

