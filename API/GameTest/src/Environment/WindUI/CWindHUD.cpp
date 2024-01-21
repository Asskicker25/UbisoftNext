#include "CWindHUD.h"
#include "../../Utilities/Remap.h"
#include "../../Timer/CTimer.h"
#include "../../Utilities/Lerp.h"

CWindHUD::CWindHUD() : CGameObject()
{
	pSprite = App::CreateSprite("Assets/Sprites/Arrow.png", 1, 1);
	mIsUI = true;
	mOrder = 5;
	
	float x = (APP_VIRTUAL_WIDTH * 0.5f);
	float y = APP_VIRTUAL_HEIGHT - 100;

	SetPosition(x, y, true);


	mWindText = new CGameObject();
	mWindText->pSprite = App::CreateSprite("Assets/Sprites/Wind.png", 1, 1);
	mWindText->mIsUI = true;
	mWindText->mOrder = 2;
	mWindText->SetPosition(x, y + 50, true);
	mWindText->pSprite->SetScale(0.4);
}

void CWindHUD::Start()
{
	CGameObject::Start();
}

void CWindHUD::Update()
{
	CGameObject::Update();

	float angle = remap(mDirection, -1, 1, -180, 0) * PI / 180;

	float direction = mDirection > 0 ? 1 : -1;

	float intensity = std::abs(mDirection);

	angle = direction == 1 ? 0 : -180;

	angle += std::sin(CTimer::GetInstance().mGameTime * ((intensity + 0.1f) * 20)) * 8;

	angle *= PI / 180;

	pSprite->SetAngle(Lerp(pSprite->GetAngle(), angle, CTimer::GetInstance().mDeltaTime * 10.0f));
}

void CWindHUD::Render()
{
	CGameObject::Render();
	App::Print(450, 600, ("Wind : " + std::to_string(mDirection)).c_str(), 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
}

void CWindHUD::SetDirection(float direction)
{
	mDirection = direction;
}

void CWindHUD::Cleanup()
{
	mWindText->Cleanup();
	CGameObject::Cleanup();
}

void CWindHUD::OnDestroy()
{
	CGameObject::OnDestroy();
}

