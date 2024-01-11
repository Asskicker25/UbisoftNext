#include "CLevelManager.h"
#include "Levels/CLevelOne.h"
#include "../GameManager/CGameManager.h"

CLevelManager& CLevelManager::GetInstance()
{
	static CLevelManager instance;
	return instance;
}

void CLevelManager::Start()
{
	AddLevel(new CLevelOne());

	pCurrentLevel = mListOfLevels[currentLevelIndex];
}

void CLevelManager::Update()
{
	if (pCurrentLevel == nullptr) return;


}

void CLevelManager::Render()
{
}

void CLevelManager::AddLevel(CBaseLevel* level)
{
	mListOfLevels.push_back(level);
}

void CLevelManager::RemoveLevel(CBaseLevel* level)
{
	mListOfLevels.erase(std::remove(mListOfLevels.begin(), mListOfLevels.end(), level), mListOfLevels.end());
}

void CLevelManager::StartLevel()
{
	pCurrentLevel->Start();
}

void CLevelManager::NextLevel()
{
	currentLevelIndex++;

	if (currentLevelIndex > mListOfLevels.size())
	{
		if (OnAllLevelsComplete != nullptr)
		{
			OnAllLevelsComplete();
		}
	}

	if (OnNextLevel == nullptr) return;

	OnNextLevel();
}

void CLevelManager::Cleanup()
{
	if (pCurrentLevel != nullptr)
	{
		pCurrentLevel->Cleanup();
	}

	for (CBaseLevel* level : mListOfLevels)
	{
		delete level;
	}

	mListOfLevels.clear();
}


