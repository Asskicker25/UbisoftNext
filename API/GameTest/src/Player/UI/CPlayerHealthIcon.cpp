#include "CPlayerHealthIcon.h"

CPlayerHealthIcon::CPlayerHealthIcon() : CGameObject()
{
	mIsUI = true;
	pSprite = App::CreateSprite("Assets/Sprites/Heart_strip2.png", 2, 1);

	pSprite->CreateAnimation(0, 1.0f / 6, { 0 });
	pSprite->CreateAnimation(1, 1.0f / 6, { 1 });
	pSprite->SetAnimation(0);

	pSprite->SetScale(1.0f);

}

void CPlayerHealthIcon::Start()
{
	CGameObject::Start();
}

void CPlayerHealthIcon::Update()
{
	CGameObject::Update();
}

void CPlayerHealthIcon::Render()
{
	CGameObject::Render();
}

void CPlayerHealthIcon::Cleanup()
{
	CGameObject::Cleanup();
}

void CPlayerHealthIcon::OnDestroy()
{
	CGameObject::OnDestroy();
}
