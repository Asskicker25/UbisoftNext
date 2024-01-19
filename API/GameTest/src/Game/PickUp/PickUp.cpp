#include "PickUp.h"

CPickUp::CPickUp()
{
	pSprite = App::CreateSprite("Assets/Sprites/Pickup.png", 1, 1);
	mTag = "Pickup";

	pPhysicsShape = new CPhysicsShape(pSprite, BOX);
}

void CPickUp::Start()
{

}

void CPickUp::Update()
{
	CGameObject::Update();
}

void CPickUp::Render()
{
	CGameObject::Render();
}

void CPickUp::Cleanup()
{
	CGameObject::Cleanup();
}

void CPickUp::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CPickUp::CopyFromOther(CGameObject* other)
{
	CGameObject::CopyFromOther(other);
}