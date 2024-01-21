#include "CWindHUD.h"
#include "../../Utilities/Remap.h"

CWindHUD::CWindHUD() : CGameObject()
{
	pSprite = App::CreateSprite("Assets/Sprites/Arrow.png", 1, 1);
	mIsUI = true;
	
	float x = (APP_VIRTUAL_WIDTH * 0.5f);
	float y = APP_VIRTUAL_HEIGHT - 100;

	SetPosition(x, y, true);
}

void CWindHUD::Start()
{
	CGameObject::Start();
}

void CWindHUD::Update()
{
	CGameObject::Update();
}

void CWindHUD::Render()
{
	CGameObject::Render();
}

void CWindHUD::Cleanup()
{
	CGameObject::Cleanup();
}

void CWindHUD::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CWindHUD::SetDirection(float direction)
{

	float angle = remap(direction, -1, 1, -180, 0) * PI / 180;

	pSprite->SetAngle(angle);

}
