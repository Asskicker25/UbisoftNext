#include "CNumberUI.h"

CNumberUI::CNumberUI()
{
	pSprite = App::CreateSprite("Assets/Sprites/Numbers_strip10.png", 10, 1);

	for (int i = 0; i < 10; i++)
	{
		pSprite->CreateAnimation(i, 1, {i});
	}

	pSprite->SetAnimation(0);

	mIsUI = true;
}

void CNumberUI::Start()
{
	CGameObject::Start();
}

void CNumberUI::Update()
{
	CGameObject::Update();
}

void CNumberUI::Render()
{
	CGameObject::Render();
}

void CNumberUI::Cleanup()
{
	CGameObject::Cleanup();
}

void CNumberUI::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CNumberUI::SetNumber(int number)
{
	pSprite->SetAnimation(number);
}
