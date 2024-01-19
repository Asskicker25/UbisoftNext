#pragma once

#include "BaseBullet.h"
#include "../../ObjectPooling/ObjectPool.h"

enum BulletType
{
	NORMAL = 0,

};

class BulletFactory
{
public:

	BaseBullet* CreateBullet(BulletType type);

private:
	std::unordered_map<BulletType, CGameObjectPool* > mListOfObjectPools;
};

