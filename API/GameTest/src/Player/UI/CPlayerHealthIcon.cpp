#include "CPlayerHealthIcon.h"

CPlayerHealthIcon::CPlayerHealthIcon() : CGameObject()
{
	mIsUI = true;
	pSprite = App::CreateSprite("Assets/Sprites/Cat_strip35.png", 35, 1);

	pSprite->CreateAnimation(0, 1.0f / 6, { 0,1,2,3 });
	pSprite->SetAnimation(1);

	pSprite->SetScale(0.75f);

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
