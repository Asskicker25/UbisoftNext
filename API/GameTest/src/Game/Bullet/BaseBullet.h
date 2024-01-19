#pragma once

#include "../../Entities/CGameObject.h"

class BaseBullet : public CGameObject
{
public:

	BaseBullet();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	virtual void CopyFromOther(BaseBullet* other);


	float mSpeed = 0;

	float mDamage = 0;

	Vector2 mMoveDir;
	
};

