#include "CEntity.h"
#include "CEntityManager.h"

void CEntity::InitializeEntity(CEntity* entity)
{
	CEntityManager::GetInstance().AddEntity(entity);
}

CEntity::CEntity()
{
	CEntityManager::GetInstance().AddEntity(this);
}

CEntity::~CEntity()
{
	CEntityManager::GetInstance().RemoveEntity(this);
}