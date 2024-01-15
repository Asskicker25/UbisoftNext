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

template<typename T>
void CObjectPool<T>::Resize()
{
	mListOfObjects.resize(mListOfObjects.size() + mResizeAmount, new T());
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
