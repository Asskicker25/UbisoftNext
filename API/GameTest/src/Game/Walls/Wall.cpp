#include "Wall.h"

CWall::CWall()
{
	pSprite = App::CreateSprite("Assets/Sprites/Wall.png", 1, 1);
	pSprite->SetScale(3);
	mTag = "Wall";

	pPhysicsShape = new CPhysicsShape(pSprite, CIRCLE);
}

void CWall::Start()
{
	CGameObject::Start();
}

void CWall::Update()
{
	CGameObject::Update();
}

void CWall::Render()
{
	CGameObject::Render();
}

void CWall::Cleanup()
{
	CGameObject::Cleanup();
}

void CWall::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CWall::CopyFromOther(CGameObject* other)
{
	CGameObject::CopyFromOther(other);
}
