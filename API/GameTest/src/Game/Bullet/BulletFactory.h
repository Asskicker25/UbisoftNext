#pragma once

#include "BaseBullet.h"
#include "../../ObjectPooling/ObjectPool.h"
#include "NormalBullet.h"



class BulletFactory
{
public:

	BaseBullet* CreateBullet(BulletType type);
	void DestroyBullet(BaseBullet* bullet,float time);

private:
	CGameObjectPool<NormalBullet>* bulletPool = nullptr;
	//std::unordered_map<BulletType, CGameObjectPool* > mListOfObjectPools;
};

