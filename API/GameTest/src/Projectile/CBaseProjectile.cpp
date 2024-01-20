#include "CBaseProjectile.h"
#include "../Timer/CTimer.h"
#include "../Utilities/Lerp.h"
#include "../World/CWorld.h"

CBaseProjectile::CBaseProjectile() : CGameObject()
{
}

void CBaseProjectile::Start()
{
	CGameObject::Start();
}

void CBaseProjectile::Update()
{
	CGameObject::Update();

	if (!mCanMove) return;


	mTimeStep = CalculateTForSpeed(mTimeStep, CTimer::GetInstance().mDeltaTime, mSpeed);

	SetPositionFromArc();

	if (mTimeStep == 1)
	{
		mCanMove = false;
	}

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

void CBaseProjectile::SetPositionFromArc()
{
	Vector2 pos = GetPositionFromArc(mTimeStep);

	pos.x += mOriginInitPos.x;
	pos.y += mOriginInitPos.y;

	SetPosition(pos.x, pos.y, true);
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

	mTimeStep = 0;

	mCanMove = true;

	mIsVisible = true;
	mIsEnabled = true;

	SetPositionFromArc();
}

