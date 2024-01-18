#pragma once

#include "CGameState.h"
#include <unordered_map>


// CGameManager class: Manages the game states and serves as the entry point to the game.
class CGameManager
{

public:

	// Initializes the game manager.
	void Start();

	// Updates the current game state.
	void Update();

	// Renders the current game state.
	void Render();

	// Adds a new game state to the manager.
	// Parameters:
	//   state - The enumerated value representing the new game state.
	//   stateInstance - A pointer to the instance of the CGameState associated with the new state.
	void AddState(EGameState state, CGameState* stateInstance);

	// Removes a game state from the manager.
	// Parameters:
	//   state - The enumerated value representing the game state to be removed.
	void RemoveState(EGameState state);

	// Changes the current game state.
	// Parameters:
	//   state - The enumerated value representing the new current game state.
	void ChangeState(EGameState state);

	// Cleans up resources and performs necessary tasks before exiting the game.
	void Cleanup();

private:

	// Prints information about the current game state to the window.
	void PrintGameState();

	// Map to store game states with their corresponding enumerated values.
	std::unordered_map<EGameState, CGameState*> mListOfStates;

	// Pointer to the current game state instance.
	CGameState* pCurrentGameState = nullptr;

	// Enumerated value representing the current game state.
	EGameState eCurrentGameState = MAIN_MENU;

	// String containing the message prefix for displaying the current game state.
	const std::string mGameStateMessage = "Current Game State : ";

	// String containing the formatted current game state information.
	std::string mGameStateString;
};


