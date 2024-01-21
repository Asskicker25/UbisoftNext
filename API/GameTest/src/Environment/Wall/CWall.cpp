#include "CWall.h"
#include "../../Utilities/Random.h"
#include "../../Tween/CTweenManager.h"

CWall::CWall()
{
	pSprite = App::CreateSprite("Assets/Sprites/Wall.png",1,1);
	pPhysicsShape = new CPhysicsShape(this, BOX);

	mTag = "Environment";
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

void CWall::ChangePosition()
{
	float x, y;

	pSprite->GetPosition(x, y);

	float yValue = GetRandomFloatNumber(mYRange.x, mYRange.y);

	CTweenManager::GetInstance().AddFloatTween(y, yValue, 2, [this](float value)
		{
			float x, y;
			pSprite->GetPosition(x, y);
			pSprite->SetPosition(x, value);
		});
}
