#include "CEntityManager.h"

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

	for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		if (!it->second->mIsStartInvoked && it->second->mIsEnabled)
		{
			it->second->Start();
			it->second->mIsStartInvoked = true;
		}

		it->second->Update();
	}
}

void CEntityManager::Render()
{
	std::unordered_map<std::string, CEntity*>::iterator it;

	for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		it->second->Render();
	}
}

void CEntityManager::Cleanup()
{
	std::unordered_map<std::string, CEntity*>::iterator it;

	for (it = mListOfEntities.begin(); it != mListOfEntities.end(); ++it)
	{
		it->second->Cleanup();
	}
}

void CEntityManager::AddEntity(CEntity* entity)
{
	std::string entityId = std::to_string(mEntityCount);

	AddEntity(entityId, entity);
}

void CEntityManager::AddEntity(std::string entityId, CEntity* entity)
{
	mListOfEntities[entityId] = entity;
	entity->mEntityId = entityId;

	mEntityCount++;
}

void CEntityManager::RemoveEntity(CEntity* entity)
{

	mListOfEntities[entity->mEntityId]->Cleanup();
	mListOfEntities.erase(entity->mEntityId);
}
