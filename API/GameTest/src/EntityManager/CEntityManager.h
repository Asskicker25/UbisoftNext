#pragma once

#include "CEntity.h"

// Singleton class responsible for managing entities in the game.
class CEntityManager
{

public: 

	// Returns a reference to the singleton instance of CEntityManager.
	static CEntityManager& GetInstance();

	// Initializes the entity manager.
	void Start();

	// Updates all registered entities.
	void Update();

	// Renders all registered entities.
	void Render();

	// Cleans up resources and performs necessary tasks before exiting the game.
	void Cleanup();

	// AddEntity method: Adds an entity to the entity manager.
	// Parameters:
	//   entity - A pointer to the entity to be added.
	void AddEntity(CEntity* entity);

	// AddEntity method (overloaded): Adds an entity to the entity manager with a specified ID.
	// Parameters:
	//   entityId - A unique identifier for the entity.
	//   entity - A pointer to the entity to be added.
	void AddEntity(std::string entityId , CEntity* entity);

	// RemoveEntity method: Removes an entity from the entity manager.
	// Parameters:
	//   entity - A pointer to the entity to be removed.
	void RemoveEntity(CEntity* entity);

	void SortEntities();

	// GetEntitiesWithTag method: Retrieves all entities with a specific tag.
	// Parameters:
	//   tag - The tag to filter entities.
	// Returns:
	//   A vector of pointers to entities with the specified tag.
	std::vector<CEntity*> GetEntitiesWithTag(const std::string& tag);

private:


	// Map to store entities with their unique IDs.
	std::unordered_map<std::string, CEntity*> mListOfEntities;

	// Count of registered entities.
	int mEntityCount = 0;
};

