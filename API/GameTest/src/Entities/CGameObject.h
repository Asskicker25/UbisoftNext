#pragma once

#include "../EntityManager/CEntity.h"

class CGameObject : public CEntity
{

public:

	CSimpleSprite* pSprite = nullptr;

	CGameObject();
	~CGameObject();

	// Inherited via CEntity
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void Destroy();
	virtual void OnDestroy();
};

