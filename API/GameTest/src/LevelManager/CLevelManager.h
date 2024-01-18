#pragma once

#include <unordered_map>
#include <functional>
#include "CBaseLevel.h"
#include "../Events/Events.h"

// Singleton class responsible for managing game levels.
class CLevelManager
{

public:

	// Initializes the level manager.
	CLevelManager();

	// Returns a reference to the singleton instance of CLevelManager.
	static CLevelManager& GetInstance();

	// Initiates the level manager.
	void Start();

	// Updates the current game level.
	void Update();

	// Renders the current game level.
	void Render();

	// AddLevel method: Adds a game level to the level manager.
	// Parameters:
	//   level - A pointer to the game level to be added.
	void AddLevel(CBaseLevel* level);

	// RemoveLevel method: Removes a game level from the level manager.
	// Parameters:
	//   level - A pointer to the game level to be removed.
	void RemoveLevel(CBaseLevel* level);

	// Initiates the current game level.
	void StartLevel();

	//Restarts the current game level.
	void RestartLevel();

	// NextLevel method: Advances to the next game level.
	// Returns:
	//   True if there is a next level, false otherwise.
	bool NextLevel();


	// Cleans up resources and performs necessary tasks before exiting the game.
	void Cleanup();

	// Callback function triggered when transitioning to the next level.
	CEvents OnNextLevel;

private:

	std::vector<CBaseLevel*> mListOfLevels;					// Vector to store registered game levels.

	CBaseLevel* pCurrentLevel = nullptr;					// Pointer to the current game level.	

	int mCurrentLevelIndex = 0;								// Index representing the current position in the list of game levels.

	// Center coordinates of the game window.
	float mWindowCenterX = 0;								
	float mWindowCenterY = 0;
};
