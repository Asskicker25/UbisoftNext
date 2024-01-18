#include "ObjectPool.h"
#include "../TimerEvents/CTimerEventsHandler.h"

#pragma region CObjectPool

template<typename T>
void CObjectPool<T>::SetPoolObject(T* poolObject)
{
	this->mPoolObject = poolObject;
	Cleanup();

	Resize();
}

template<typename T>
void CObjectPool<T>::Cleanup()
{
	for (T* t : mListOfObjects)
	{
		delete t;
	}
	mListOfObjects.clear();
}

#pragma endregion


CGameObject* CGameObjectPool::SpawnObject()
{
	// Iterate through the list to find an inactive CGameObject.
	for (CGameObject* gameObject : mListOfObjects)
	{
		if (gameObject->mIsVisible == false)
		{
			gameObject->mIsVisible = true;
			gameObject->mIsEnabled = true;

			return gameObject;
		}
	}

	// If no inactive CGameObjects are found, resize the pool and return the last element.
	int listSize = mListOfObjects.size();

	Resize();

	return mListOfObjects[listSize];
}

void CGameObjectPool::DestroyObject(CGameObject* poolObject)
{
	poolObject->mIsEnabled = false;
	poolObject->mIsVisible = false;
}

void CGameObjectPool::DestroyObject(CGameObject* poolObject, float delayTime)
{
	CTimerEventsHandler::GetInstance().AddDelay([poolObject]()
		{
			poolObject->mIsEnabled = false;
			poolObject->mIsVisible = false;
		}, delayTime, &poolObject->OnDestroyEvent);
}


void CGameObjectPool::SetPoolObject(CGameObject* poolObject)
{
	CObjectPool::SetPoolObject(poolObject);

}

void CGameObjectPool::Cleanup()
{
	CObjectPool::Cleanup();
}

void CGameObjectPool::Resize()
{
	// Store the previous size of the pool.
	int prevSize = mListOfObjects.size();

	// Resize the pool by adding elements.
	mListOfObjects.resize(mListOfObjects.size() + mResizeAmount);

	// Initialize new elements in the pool.
	for (int i = prevSize; i < mListOfObjects.size(); i++)
	{
		mListOfObjects[i] = new CGameObject();
		mListOfObjects[i]->CopyFromOther(mPoolObject);
		mListOfObjects[i]->mIsEnabled = false;
		mListOfObjects[i]->mIsVisible = false;

		// Misc: Adjust position for visual separation.
		float x, y;
		mListOfObjects[i]->pSprite->GetPosition(x, y);
		x += i * 20;
		mListOfObjects[i]->pSprite->SetPosition(x, y);
	}
}

