#include "BaseBullet.h"

BaseBullet::BaseBullet() : CGameObject()
{
	int a = 10;
}

void BaseBullet::Start()
{
	CGameObject::Start();
}

void BaseBullet::Update()
{
	CGameObject::Update();
}

void BaseBullet::Render()
{
	CGameObject::Render();
}

void BaseBullet::Cleanup()
{
	CGameObject::Cleanup();
}

void BaseBullet::OnDestroy()
{
	CGameObject::OnDestroy();
}

void BaseBullet::CopyFromOther(BaseBullet* other)
{
	CopyFromOther(other);
}

