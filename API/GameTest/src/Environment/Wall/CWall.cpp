#include "CWall.h"
#include "../../Utilities/Random.h"
#include "../../Tween/CTweenManager.h"

CWall::CWall()
{
	pSprite = App::CreateSprite("Assets/Sprites/Obstacle_strip12.png",12,1);

	pSprite->CreateAnimation(0, 1.0f / 6.0f, { 0,1,2,3,4,5 });
	pSprite->CreateAnimation(1, 1.0f / 6.0f, { 6,7,8,9,10,11 });

	pSprite->SetAnimation(0);

	pSprite->SetScale(1.3);

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
