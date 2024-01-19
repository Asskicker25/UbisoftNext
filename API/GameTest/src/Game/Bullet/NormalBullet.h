#pragma once

#include "BaseBullet.h"

class NormalBullet : public BaseBullet
{
public:

	NormalBullet();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	// CopyFromOther - Copies data from another game object.
	// Parameters:
	//   other - A pointer to the game object to copy properties from.
	virtual void CopyFromOther(NormalBullet* other);
};

