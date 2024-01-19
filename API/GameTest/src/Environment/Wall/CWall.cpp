#include "CWall.h"

CWall::CWall()
{
	pSprite = App::CreateSprite("Assets/Sprites/Wall.png",1,1);
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
