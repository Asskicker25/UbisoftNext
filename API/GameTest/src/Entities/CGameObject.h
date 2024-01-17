#pragma once

#include "../EntityManager/CEntity.h"
#include "../Physics/CPhysicsShape.h"
#include "../Physics/Shapes/CPhysicsShapeCircle.h"
#include "../Physics/Shapes/CPhysicsShapeBox.h"

class CGameObject : public CEntity
{

public:

	bool mIsVisible = true;
	std::string mName = "Unnamed";

	CSimpleSprite* pSprite = nullptr;
	CPhysicsShape* pPhysicsShape = nullptr;

	CGameObject();
	~CGameObject();

	// Inherited via CEntity
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();
	virtual void CopyFromOther(CGameObject* other);
};

