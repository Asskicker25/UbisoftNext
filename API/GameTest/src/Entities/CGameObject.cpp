#include "CGameObject.h"
#include "../EntityManager/CEntityManager.h"
#include "../Timer/CTimer.h"

CGameObject::CGameObject()
{
}

// Cleans up resources associated with the game object.
CGameObject::~CGameObject()
{
	delete pSprite;
	delete pPhysicsShape;
}

void CGameObject::Start()
{
}

void CGameObject::Update()
{
	if (pSprite == nullptr) return;

	// Update the sprite with the current delta time.
	pSprite->Update(CTimer::GetInstance().mDeltaTime);
}

void CGameObject::Render()
{
	// Check if the game object is set to be invisible.
	if (!mIsVisible) return;

	if (pSprite != nullptr)
	{
		// Draw the sprite if available.
		pSprite->SetOpacity(mOpacity);
		pSprite->Draw();

	}

	if (!RENDER_PHYSICS) return;

	// Render the physics shape if available.
	if (pPhysicsShape != nullptr)
	{
		pPhysicsShape->Render();
	}

}

void CGameObject::Cleanup()
{
	// Delete the current game object instance.
	delete this;
}

void CGameObject::OnDestroy()
{
	// Invoke the Cleanup method.
	Cleanup();
}

void CGameObject::CopyFromOther(CGameObject* other)
{
	// Call the base class method to copy common entity properties.
	CEntity::CopyFromOther(other);
	
	// Delete the existing sprite instance.
	if (pSprite != nullptr) { delete pSprite; }

	// Create a new sprite instance and copy data from the other game object's sprite.
	pSprite = new CSimpleSprite(other->pSprite);

	// Delete the existing physicsShape instance.
	if (pPhysicsShape != nullptr) { delete pPhysicsShape; }

	if (other->pPhysicsShape == nullptr) return;

	// Create a new physicsShape instance and copy data from the other game object's physicsShape.
	pPhysicsShape = new CPhysicsShape(pSprite, other->pPhysicsShape);

}
