#pragma once

#include "CEntity.h"


class CEntityManager
{

public: 

	static CEntityManager& GetInstance();

	void Start();
	void Update();
	void Render();
	void Cleanup();

	void AddEntity(CEntity* entity);
	void AddEntity(std::string entityId , CEntity* entity);
	void RemoveEntity(CEntity* entity);

private:
	std::unordered_map<std::string, CEntity*> mListOfEntities;

	int mEntityCount = 0;
};

