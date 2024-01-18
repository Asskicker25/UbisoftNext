#include "CLevelManager.h"
#include "../Levels/CLevelOne.h"
#include "../Levels/CLevelTwo.h"
#include "../GameManager/CGameManager.h"
#include "../EntityManager/CEntityManager.h"

CLevelManager::CLevelManager()
{
	mWindowCenterX = APP_VIRTUAL_WIDTH / 2;
	mWindowCenterY = APP_VIRTUAL_HEIGHT / 2;

	// Add initial levels to the list (e.g., CLevelOne and CLevelTwo).
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
	// Check if there is a valid current level.
	if (pCurrentLevel == nullptr) return;

	// Check if the current level is complete.
	if (pCurrentLevel->IsLevelComplete())
	{
		// Clean up the current level.
		pCurrentLevel->Cleanup();
		pCurrentLevel = nullptr;

		// Invoke the event for transitioning to the next level.
		OnNextLevel.Invoke();

		return;
	}

	// Update the current level.
	pCurrentLevel->Update();
}

void CLevelManager::Render()
{
	// Check if there is a valid current level.
	if (pCurrentLevel == nullptr) return;

	pCurrentLevel->Render();

	// Display the level number on the screen.
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

void CLevelManager::RestartLevel()
{
	pCurrentLevel->Cleanup();
	pCurrentLevel->Start();
}

bool CLevelManager::NextLevel()
{
	mCurrentLevelIndex++;

	// Check if there is a next level in the list.
	if (mCurrentLevelIndex >= mListOfLevels.size())
	{
		return false;
	}
	
	// Set the current level to the next level in the list.
	pCurrentLevel = mListOfLevels[mCurrentLevelIndex];

	return true;
}

void CLevelManager::Cleanup()
{
	// Check if there is a valid current level and invoke its shutdown method.
	if (pCurrentLevel != nullptr)
	{
		pCurrentLevel->Cleanup();
	}

	// Delete all level instances in the list.
	for (CBaseLevel* level : mListOfLevels)
	{
		delete level;
	}

	// Clear the list of levels.
	mListOfLevels.clear();
}


