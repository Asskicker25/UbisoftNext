#pragma once

#include "../EntityManager/CEntity.h"
#include "../Physics/CPhysicsShape.h"
#include "../Physics/Shapes/CPhysicsShapeCircle.h"
#include "../Physics/Shapes/CPhysicsShapeBox.h"

// Represents a game object with visual and physical properties.
class CGameObject : public CEntity
{

public:

	bool mIsVisible = true;					// Flag indicating whether the game object is visible.
	float mOpacity = 1.0f;

	// Pointers to sprite and physics shape instances.
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

	// CopyFromOther - Copies data from another game object.
	// Parameters:
	//   other - A pointer to the game object to copy properties from.
	virtual void CopyFromOther(CGameObject* other);
};

