#include "CPowerUpUI.h"


CPowerUpUI::CPowerUpUI()
{
	mIsUI = true;
	mOrder = 2;

	mSelected = new CGameObject();
	mSelected->pSprite = App::CreateSprite("Assets/Sprites/Circle.png", 1, 1);
	mSelected->mIsUI = true;
	mSelected->mOrder = 2;
	mSelected->mOpacity = 0.4f;
	mSelected->mIsVisible = false;
	mSelected->pSprite->SetScale(0.52);
	mSelected->pSprite->SetColor(0.4, 0.4, 0.4);

	mCount = new CGameObject();
	mCount->pSprite = App::CreateSprite("Assets/Sprites/Numbers_strip10.png", 10, 1);
	mCount->mIsUI = true;
	mCount->mOrder = 3;
	mCount->pSprite->SetScale(0.7);

	for (int i = 0; i < 10; i++)
	{
		mCount->pSprite->CreateAnimation(i, 1, { i });
	}
}

void CPowerUpUI::Start()
{
	CGameObject::Start();
}

void CPowerUpUI::Update()
{
	float x, y;
	pSprite->GetPosition(x, y);

	mSelected->SetPosition(x , y , true);
	mCount->SetPosition(x + mOffset, y + mOffset, true);

	CGameObject::Update();
}

void CPowerUpUI::Render()
{
	CGameObject::Render();
}

void CPowerUpUI::Cleanup()
{
	mCount->Cleanup();
	mSelected->Cleanup();
	CGameObject::Cleanup();
}

void CPowerUpUI::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CPowerUpUI::SetCount(int count)
{
	mOpacity = count == 0 ? 0.2f : 1.0f;

	mCount->pSprite->SetAnimation(count);
}

void CPowerUpUI::SetVisibility(bool state, bool isSelected)
{
	mIsVisible = state;
	mCount->mIsVisible = state;
	mSelected->mIsVisible = state? isSelected : state;

}


