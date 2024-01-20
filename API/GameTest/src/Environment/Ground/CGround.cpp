#include "CGround.h"

CGround::CGround() : CGameObject()
{
	pSprite = App::CreateSprite("Assets/Sprites/Wall.png", 1, 1);

}

void CGround::Start()
{
	CGameObject::Start();
}

void CGround::Update()
{
	CGameObject::Update();
}

void CGround::Render()
{
	CGameObject::Render();
}

void CGround::Cleanup()
{
	CGameObject::Cleanup();
}

void CGround::OnDestroy()
{
	CGameObject::OnDestroy();
}
