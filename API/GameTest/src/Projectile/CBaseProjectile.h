#pragma once

#include "../Entities/CGameObject.h"
#include "../Events/Events.h"

enum EProjectileType
{
	NORMAL = 0,

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

private:

	Vector2 GetPositionFromArc(float t);
	void SetPositionFromArc();

	void HandleFreeFall();
	void HandleFollowArc();
	void HandleCollision();
	void HandleProjectileExplode();

	bool mFollowArc = false;
	bool mFreeFall = false;

	float mTimeStep = 0;
	float mSpeed = 0.4f;
	float mFreeFallSpeed = 10.0f;

	Vector2 mOriginInitPos;
	Vector2 mFreeFallDir;

	std::vector<Vector2> mArcPath;

};

