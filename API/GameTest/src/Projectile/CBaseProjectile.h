#pragma once

#include "../Entities/CGameObject.h"
#include "../Events/Events.h"

enum EProjectileType
{
	NORMAL = 0,
	DAMAGE_AMPLIFIER_PROJECTILE = 1,
	EXPLOSIVE_IMPACT_PROJECTILE = 2
};

class CBaseProjectile : public CGameObject
{
public:
	CBaseProjectile();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	virtual void CopyFromOther(CBaseProjectile* other);

	void Shoot(std::vector<Vector2>& arcPath);

	CEvents OnProjectileFail;
	CEvents OnProjectileSuccess;

	int mDamageAmount = 1;

private:

	Vector2 GetPositionFromArc(float t);
	void SetPositionFromArc();

	void HandleFreeFall();
	void HandleFollowArc();
	void HandleCollision();
	void HandleProjectileExplode();
	void CalculateArcDistance();

	bool mFollowArc = false;
	bool mFreeFall = false;

	float mTimeStep = 0;
	float mSpeed = 500.0f;
	float mFreeFallSpeed = 10.0f;
	float mTotalTime = 0;

	float mArcDistance = 0;

	Vector2 mOriginInitPos;
	Vector2 mFreeFallDir;

	std::vector<Vector2> mArcPath;

};

