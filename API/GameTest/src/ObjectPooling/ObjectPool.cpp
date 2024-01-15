#include "ObjectPool.h"

#pragma region CObjectPool

template<typename T>
void CObjectPool<T>::SetPoolObject(T* poolObject)
{
	this->mPoolObject = poolObject;

	for (T* t : mListOfObjects)
	{
		delete t;
	}

	mListOfObjects.clear();

	Resize();
}


#pragma endregion


CGameObject* CGameObjectPool::SpawnObject()
{
	return nullptr;
}

CGameObject* CGameObjectPool::DestroyObject()
{
	return nullptr;
}

void CGameObjectPool::SetPoolObject(CGameObject* poolObject)
{
	CObjectPool::SetPoolObject(poolObject);

}

void CGameObjectPool::Resize()
{
	int prevSize = mListOfObjects.size();
	mListOfObjects.resize(mListOfObjects.size() + mResizeAmount);

	for (int i = prevSize; i < mListOfObjects.size(); i++)
	{
		mListOfObjects[i] = new CGameObject();
		mListOfObjects[i]->CopyFromOther(mPoolObject);
		float x, y;
		mListOfObjects[i]->pSprite->GetPosition(x, y);
		x += i * 10;
		mListOfObjects[i]->pSprite->SetPosition(x, y);
	}
}
