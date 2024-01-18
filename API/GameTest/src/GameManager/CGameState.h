#pragma once

#include "EGameState.h"
#include "../../App/app.h"
#include <string>

class CGameManager;

// Abstract base class for all game states.
class CGameState
{
public:

	// Virtual destructor to ensure proper cleanup of derived classes.
	virtual ~CGameState() {};

	// Pure virtual methods to be implemented by derived classes:

	// Initiates the state.
	virtual void Start() = 0;

	// Updates the state logic.
	virtual void Update() = 0;

	// Renders the state.
	virtual void Render() = 0;

	// Cleans up resources before switching to a different state.
	virtual void Cleanup() = 0;

	// Pauses the state if applicable.
	virtual void Pause() = 0;

	// Resumes the state if it was paused.
	virtual void Resume() = 0;

	// ChangeState - Notifies the associated game manager to change the current game state.
	// Parameters:
	//   state - The enumerated value representing the new game state.
	void ChangeState(EGameState state);


	// SetGameManager - Sets the pointer to the associated game manager.
	// Parameters:
	//   gameManager - A pointer to the CGameManager instance.
	void SetGameManager(CGameManager* gameManger);

private:
	
	// Boolean indicating whether the state is currently paused.
	bool mIsPaused = false;

	// Pointer to the associated game manager.
	CGameManager* pGameManager = nullptr;

};