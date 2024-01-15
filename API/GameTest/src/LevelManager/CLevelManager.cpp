#include "CLevelManager.h"
#include "../Levels/CLevelOne.h"
#include "../Levels/CLevelTwo.h"
#include "../GameManager/CGameManager.h"

CLevelManager::CLevelManager()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;

	AddLevel(new CLevelOne());
	//AddLevel(new CLevelTwo());
}

CLevelManager& CLevelManager::GetInstance()
{
	static CLevelManager instance;
	return instance;
}

void CLevelManager::Start()
{
	mCurrentLevelIndex = 0;
	pCurrentLevel = mListOfLevels[mCurrentLevelIndex];
}

void CLevelManager::Update()
{
	if (pCurrentLevel == nullptr) return;

	if (pCurrentLevel->IsLevelComplete())
	{
		pCurrentLevel->Cleanup();
		pCurrentLevel = nullptr;

		if (OnNextLevel == nullptr) return;

		OnNextLevel();

		return;
	}

	pCurrentLevel->Update();
}

void CLevelManager::Render()
{
	if (pCurrentLevel == nullptr) return;

	pCurrentLevel->Render();

	App::Print(mWindowCenterX, 2 * mWindowCenterY - mWindowCenterY / 4,
		("Level " + std::to_string( mCurrentLevelIndex + 1)).c_str(), 0, 1, 0, GLUT_BITMAP_TIMES_ROMAN_24);

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

bool CLevelManager::NextLevel()
{
	mCurrentLevelIndex++;

	if (mCurrentLevelIndex >= mListOfLevels.size())
	{
		return false;
	}
	
	pCurrentLevel = mListOfLevels[mCurrentLevelIndex];

	return true;
}

void CLevelManager::Cleanup()
{
	if (pCurrentLevel != nullptr)
	{
		pCurrentLevel->Shutdown();
	}

	for (CBaseLevel* level : mListOfLevels)
	{
		delete level;
	}

	mListOfLevels.clear();
}


