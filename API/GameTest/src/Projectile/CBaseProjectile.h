#pragma once

#include "../Entities/CGameObject.h"

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

private:

	Vector2 GetPositionFromArc(float t);
	void SetPositionFromArc();

	bool mCanMove = false;

	float mTimeStep = 0;
	float mSpeed = 0.4f;

	Vector2 mOriginInitPos;

	std::vector<Vector2> mArcPath;

};

