#include "CGround.h"

CGround::CGround() : CGameObject()
{
	pSprite = App::CreateSprite("Assets/Sprites/Ground_strip9.png", 9, 1);

	for (int i = 0; i < 9; i++)
	{
		pSprite->CreateAnimation(i, 1, { i });
	}


	mTag = "Environment";
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
