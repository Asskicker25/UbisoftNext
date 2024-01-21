#include "CBaseProjectile.h"
#include "../Timer/CTimer.h"
#include "../Utilities/Lerp.h"
#include "../World/CWorld.h"

CBaseProjectile::CBaseProjectile() : CGameObject() 
{
	mTag = "Projectile";
}

void CBaseProjectile::Start()
{
	CGameObject::Start();
}

void CBaseProjectile::Update()
{
	CGameObject::Update();

	HandleFollowArc();
	HandleFreeFall();
	HandleCollision();

}


Vector2 CBaseProjectile::GetPositionFromArc(float t)
{
	t = max(0.0f, min(1.0f, t));

	size_t index1 = static_cast<size_t>(t * (mArcPath.size() - 1));
	size_t index2 = min(index1 + 1, mArcPath.size() - 1);

	float lerpT = t * (mArcPath.size() - 1) - index1;
	Vector2 interpolatedPosition;
	interpolatedPosition.x = Lerp(mArcPath[index1].x, mArcPath[index2].x, lerpT);
	interpolatedPosition.y = Lerp(mArcPath[index1].y, mArcPath[index2].y, lerpT);

	return interpolatedPosition;
}


void CBaseProjectile::HandleFreeFall()
{
	if (!mFreeFall) return;

	/*float x, y;
	pSprite->GetPosition(x,y);

	x += mFreeFallSpeed * mFreeFallDir.x;
	y += mFreeFallSpeed * mFreeFallDir.y;

	pSprite->SetPosition(x, y);*/

	Vector2 pos = GetPosition();
	pos.x += mFreeFallSpeed * mFreeFallDir.x;
	pos.y += mFreeFallSpeed * mFreeFallDir.y;

	SetPosition(pos.x, pos.y);
}

void CBaseProjectile::HandleFollowArc()
{
	if (!mFollowArc) return;

	//mTimeStep = CalculateTForSpeed(mTimeStep, CTimer::GetInstance().mDeltaTime, mSpeed);

	mTimeStep += CTimer::GetInstance().mDeltaTime / mTotalTime;

	SetPositionFromArc();

	if (mTimeStep >= 1)
	{
		mFollowArc = false;
		mFreeFall = true;
	}
}

void CBaseProjectile::SetPositionFromArc()
{
	Vector2 pos = GetPositionFromArc(mTimeStep);

	pos.x += mOriginInitPos.x;
	pos.y += mOriginInitPos.y;

	SetPosition(pos.x, pos.y, true);
}

void CBaseProjectile::HandleCollision()
{
	std::vector<CGameObject*> colliderObjects;

	if (CheckCollisionWithTag(pPhysicsShape, "Player", colliderObjects))
	{
		HandleProjectileExplode();
		OnProjectileSuccess.Invoke();
		return;
	}

	if (CheckCollisionWithTag(pPhysicsShape, "Environment", colliderObjects))
	{
		HandleProjectileExplode();
		OnProjectileFail.Invoke();
	}
}

void CBaseProjectile::HandleProjectileExplode()
{
	mIsEnabled = false;
	mIsVisible = false;
}


void CBaseProjectile::Render()
{
	CGameObject::Render();
}

void CBaseProjectile::Cleanup()
{
	CGameObject::Cleanup();
}

void CBaseProjectile::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CBaseProjectile::CopyFromOther(CBaseProjectile* other)
{
	CGameObject::CopyFromOther(other);
}

void CBaseProjectile::Shoot(std::vector<Vector2>& arcPath)
{
	this->mArcPath = arcPath;

	mOriginInitPos = CWorld::GetInstance().mOrigin;

	mFreeFallDir = mArcPath[mArcPath.size() - 1] - mArcPath[mArcPath.size() - 2];
	mFreeFallDir.Normalize();

	mTimeStep = 0;

	mFollowArc = true;

	mIsVisible = true;
	mIsEnabled = true;

	CalculateArcDistance();

	mTotalTime = GetTimeForDistance(mArcDistance, mSpeed);

	SetPositionFromArc();
}

void CBaseProjectile::CalculateArcDistance()
{
	mArcDistance = 0;

	for (int i = 1; i < mArcPath.size(); i++)
	{
		Vector2 diff = mArcPath[i] - mArcPath[i - 1];

		mArcDistance += std::abs(diff.Magnitude());
	}
}


