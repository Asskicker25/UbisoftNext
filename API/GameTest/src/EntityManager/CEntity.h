#pragma once

#include <unordered_map>
#include <string>
#include "../../App/app.h"
#include "../Events/Events.h"


// Abstract base class for game entities.

class CEntity
{
public:

	// Initializes the entity.
	CEntity();


	virtual ~CEntity();

	// Pure virtual methods to be implemented by derived classes:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
	virtual void OnDestroy() = 0;

	// Copies data from another entity.
	virtual void CopyFromOther(CEntity* entity);

	// Marks the entity for destruction.
	void Destroy();

	// InitializeEntity method: Initializes the entity with properties from another entity.
	// Parameters:
	//   entity - A pointer to the entity to copy properties from.
	virtual void InitializeEntity(CEntity* entity);


	CEvents OnDestroyEvent;

	std::string mEntityId = "";						// Unique identifier for the entity.
	std::string mTag = "Untagged";					// Tag to categorize the entity (default is "Untagged").
	std::string mName = "Unnamed";					// Name assigned to the entity.
	
	bool mIsEnabled = true;							// Flag indicating whether the entity is enabled.
	bool mIsStartInvoked = false;					// Flag indicating whether the Start method has been invoked for the entity.
	bool mIsUI = false;								// Flag indicating whether the entity is UI.

	int mOrder = 0;
};

