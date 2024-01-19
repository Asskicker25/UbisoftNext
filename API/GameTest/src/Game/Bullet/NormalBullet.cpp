#include "NormalBullet.h"

NormalBullet::NormalBullet() : BaseBullet()
{
	/*pSprite = App::CreateSprite("Assets/Sprite/Bullet.png", 1, 2);
	pSprite->CreateAnimation(0, 1.0f / 10.0f, { 0,1 });*/

	pSprite = App::CreateSprite("Assets/Sprites/Bullet.png", 2, 1);
	pSprite->CreateAnimation(0, 1.0f / 6.0f, { 0,1 });
	pSprite->SetAnimation(0);

	pPhysicsShape = new CPhysicsShape(pSprite, BOX);

	mSpeed = 2;
}


void NormalBullet::Start()
{
	mName = "Bullet " + mEntityId;

	BaseBullet::Start();
}

void NormalBullet::Update()
{
	float x, y;

	pSprite->GetPosition(x, y);

	x += mMoveDir.x * mSpeed;
	y += mMoveDir.y * mSpeed;

	pSprite->SetPosition(x, y);

	std::vector<CGameObject*> coll;
	if (CheckCollisionWithTag(pPhysicsShape, "Wall", coll))
	{
		mIsEnabled = false;
		mIsVisible = false;

		for (CGameObject* a : coll)
		{
			a->Destroy();
		}

		return;
	}

	BaseBullet::Update();

}

void NormalBullet::Render()
{
	this;
	BaseBullet::Render();
}

void NormalBullet::Cleanup()
{
	BaseBullet::Cleanup();
}

void NormalBullet::OnDestroy()
{
	BaseBullet::OnDestroy();
}

void NormalBullet::CopyFromOther(NormalBullet* other)
{
}
