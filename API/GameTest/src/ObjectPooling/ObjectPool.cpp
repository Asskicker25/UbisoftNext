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
	for (CGameObject* gameObject : mListOfObjects)
	{
		if (gameObject->mIsVisible == false)
		{
			gameObject->mIsVisible = true;
			gameObject->mIsEnabled = true;

			return gameObject;
		}
	}

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
		}, delayTime);
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
	int prevSize = mListOfObjects.size();
	mListOfObjects.resize(mListOfObjects.size() + mResizeAmount);

	for (int i = prevSize; i < mListOfObjects.size(); i++)
	{
		mListOfObjects[i] = new CGameObject();
		mListOfObjects[i]->CopyFromOther(mPoolObject);
		mListOfObjects[i]->mIsEnabled = false;
		mListOfObjects[i]->mIsVisible = false;

		//Misc
		float x, y;
		mListOfObjects[i]->pSprite->GetPosition(x, y);
		x += i * 20;
		mListOfObjects[i]->pSprite->SetPosition(x, y);
	}
}

