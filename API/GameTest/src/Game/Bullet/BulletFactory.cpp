#include "BulletFactory.h"
#include "NormalBullet.h"


BaseBullet* BulletFactory::CreateBullet(BulletType type)
{
	/*if (!mListOfObjectPools[type])
	{
		CGameObjectPool* bulletPool = new CGameObjectPool();

		NormalBullet* spawnObj = new NormalBullet();
		spawnObj->mIsEnabled = false;
		spawnObj->mIsVisible = false;

		bulletPool->SetPoolObject(spawnObj);

		mListOfObjectPools[type] = bulletPool;
	}

	BaseBullet* bullet = (BaseBullet*) mListOfObjectPools[type]->SpawnObject();*/

	if (bulletPool == nullptr)
	{
		bulletPool = new CGameObjectPool <NormalBullet>();

		NormalBullet* spawnObj = new NormalBullet();
		spawnObj->mIsEnabled = false;
		spawnObj->mIsVisible = false;

		bulletPool->SetPoolObject(spawnObj);
	}
	
	return bulletPool->SpawnObject();
}

void BulletFactory::DestroyBullet(BaseBullet* bullet, float time)
{
	if (bullet->bulletType == NORMAL)
	{
		bulletPool->DestroyObject((NormalBullet*)bullet, time);
	}

}

