#include "CEntityManager.h"
#include <algorithm>
#include<vector>

CEntityManager& CEntityManager::GetInstance()
{
	static CEntityManager instance;
	return instance;
}

void CEntityManager::Start()
{
}

void CEntityManager::Update()
{
	std::unordered_map<std::string, CEntity*>::iterator it;

	// Iterate through all entities and invoke their Start and Update methods.
	for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		// If Start has not been invoked yet and the entity is enabled, invoke Start.

		if (!it->second->mIsEnabled) continue;

		if (!it->second->mIsStartInvoked)
		{
			it->second->Start();
			it->second->mIsStartInvoked = true;
		}

		// Update the entity.
		it->second->Update();
	}
}

void CEntityManager::Render()
{
	std::unordered_map<std::string, CEntity*>::iterator it;

	// Iterate through all entities and invoke their Render methods.
	for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		it->second->Render();
	}
}

void CEntityManager::Cleanup()
{
	std::unordered_map<std::string, CEntity*>::iterator it;

	// Iterate through all entities, invoke their Cleanup methods, and clear the entity list.
	while (mListOfEntities.size() != 0)
	{
		mListOfEntities.begin()->second->Cleanup();
	}

	/*for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		it->second->Cleanup();
		it->second = nullptr;
	}*/
}

// Adds an entity to the entity manager with a generated ID.
void CEntityManager::AddEntity(CEntity* entity)
{
	std::string entityId = std::to_string(mEntityCount);

	AddEntity(entityId, entity);
}

// Adds an entity to the entity manager with a specified ID.
void CEntityManager::AddEntity(std::string entityId, CEntity* entity)
{
	mListOfEntities[entityId] = entity;
	entity->mEntityId = entityId;

	mEntityCount++;

}

// Removes an entity from the entity manager.
void CEntityManager::RemoveEntity(CEntity* entity)
{
	//mListOfEntities[entity->mEntityId]->Cleanup();
	mListOfEntities.erase(entity->mEntityId);
}

bool CompareByOrder(const std::pair<std::string, CEntity*>& entity1, const std::pair<std::string, CEntity*>& entity2) {
	return entity1.second->mOrder < entity2.second->mOrder;
}
void CEntityManager::SortEntities()
{
	std::vector<std::pair<std::string, CEntity*>> entityVector(mListOfEntities.begin(), mListOfEntities.end());

	std::sort(entityVector.begin(), entityVector.end(), CompareByOrder);

	mListOfEntities.clear();

	for (std::pair<std::string, CEntity*>& entityPair : entityVector) 
	{
		mListOfEntities[entityPair.first] = entityPair.second;
	}
}

// Retrieves all entities with a specific tag.
std::vector<CEntity*> CEntityManager::GetEntitiesWithTag(const std::string& tag)
{
	std::vector<CEntity*> entitiesWithTag;
	std::unordered_map<std::string, CEntity*>::iterator it;

	for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		if (it->second->mTag != tag) continue;
		
		entitiesWithTag.push_back(it->second);
	}

	return entitiesWithTag;
}
