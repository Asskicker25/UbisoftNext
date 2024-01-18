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

void CEntity::CopyFromOther(CEntity* entity)
{
	this->mIsEnabled = entity->mIsEnabled;
	this->mIsStartInvoked = false;
}

void CEntity::Destroy()
{
	OnDestroy();
	OnDestroyEvent.Invoke();
}
