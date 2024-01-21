#pragma once

#include "CGameObject.h"

class CNightManager : public CGameObject
{
public:

	CNightManager();

	// Inherited via CEntity
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	CGameObject* mNightSprite = nullptr;

private:
	void OnTurnStart();
	void OnFollowProjectile();
	void HandleProjectileFollow();
	void OnProjectileHit();

	CGameObject* mCurrentProjectile = nullptr;

	Vector2 mOriginInitPos;

	bool mCanFollow = false;
};

