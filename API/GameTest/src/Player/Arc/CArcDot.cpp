#include "CArcDot.h"

CArcDot::CArcDot() : CGameObject()
{
	pSprite = App::CreateSprite("Assets/Sprites/Circle.png", 1, 1);

	mIsEnabled = false;
	mIsVisible = false;

	mIsUI = true;

	pSprite->SetScale(0.1);
}

void CArcDot::Start()
{
	CGameObject::Start();
}

void CArcDot::Update()
{
	CGameObject::Update();
}

void CArcDot::Render()
{
	CGameObject::Render();
}

void CArcDot::Cleanup()
{
	CGameObject::Cleanup();
}

void CArcDot::OnDestroy()
{
	CGameObject::OnDestroy();
}
