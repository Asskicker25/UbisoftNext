#pragma once

#include <unordered_map>
#include <functional>
#include "CBaseLevel.h"

class CLevelManager
{

public:
	CLevelManager();

	static CLevelManager& GetInstance();

	void Start();
	void Update();
	void Render();

	void AddLevel(CBaseLevel* level);
	void RemoveLevel(CBaseLevel* level);

	void StartLevel();
	bool NextLevel();

	void Cleanup();

	std::function<void()> OnNextLevel = nullptr;

private:

	std::vector<CBaseLevel*> mListOfLevels;

	CBaseLevel* pCurrentLevel = nullptr;

	int mCurrentLevelIndex = 0;

	float mWindowCenterX = 0;
	float mWindowCenterY = 0;
};
