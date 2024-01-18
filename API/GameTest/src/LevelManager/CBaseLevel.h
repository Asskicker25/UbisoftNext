#pragma once

#include "../../App/app.h"
#include "../Entities/CGameObject.h"

// Abstract base class for game levels.
class CBaseLevel
{

public:

	// Ensures proper cleanup of derived classes.
	virtual ~CBaseLevel() {};

	// Pure virtual methods to be implemented by derived classes:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	// Cleans up resources and performs necessary tasks after completing the level.
	virtual void Cleanup() = 0;				

	// Cleans up resources and performs necessary tasks when exiting the application.
	virtual void Shutdown() = 0;	

	// IsLevelComplete - Checks if the conditions for completing the level are met.
	// Returns:
	//   True if the level is complete, false otherwise.
	virtual bool IsLevelComplete() = 0;

};

