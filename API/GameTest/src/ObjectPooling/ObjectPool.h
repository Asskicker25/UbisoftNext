#pragma once

#include <vector>
#include "../Entities/CGameObject.h"
#include "../TimerEvents/CTimerEventsHandler.h"


// Abstract base class for object pooling.

template <typename T>
class CObjectPool
{
public:

	// Ensures proper cleanup of derived classes.
	virtual ~CObjectPool() {};

	// Pure virtual methods to be implemented by derived classes:

	virtual T* SpawnObject() = 0;								// Creates and returns a new object from the pool.
	virtual void SetPoolObject(T* poolObject);					// Assigns a prototype object to the pool for initialization.
	virtual void Resize() = 0;									// Adjusts the size of the object pool.
	virtual void Cleanup();										// Cleans up resources and resets the object pool.
	virtual void DestroyObject(T* object) = 0;					// Marks an object as inactive in the pool.
	virtual void DestroyObject(T* object, float delayTime) = 0;	// Marks an object as inactive with a delay before reusing it.
	void Test() {};

	int mResizeAmount = 10;									// Amount to resize the pool by when reaching its capacity.
	std::vector<T*> mListOfObjects;							// Vector to store objects in the pool.
	T* mPoolObject;											// Prototype object for initializing the pool.

};

template <typename T>
class CGameObjectPool : public CObjectPool<T>
{
public:
	T* SpawnObject() override;
	void DestroyObject(T* poolObject) override;
	void DestroyObject(T* poolObject, float delayTime) override;
	void SetPoolObject(T* poolObject) override;
	void Cleanup() override;
	void Resize() override;
};



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


template <typename T>
T* CGameObjectPool<T>::SpawnObject()
{
    for (T* gameObject : this->mListOfObjects)
    {
        if (!gameObject->mIsVisible)
        {
            gameObject->mIsVisible = true;
            gameObject->mIsEnabled = true;
            return gameObject;
        }
    }

    int listSize = this->mListOfObjects.size();
    this->Resize();
    return this->mListOfObjects[listSize];
}

template <typename T>
void CGameObjectPool<T>::DestroyObject(T* poolObject)
{
    poolObject->mIsEnabled = false;
    poolObject->mIsVisible = false;
}

template <typename T>
void CGameObjectPool<T>::DestroyObject(T* poolObject, float delayTime)
{
    CTimerEventsHandler::GetInstance().AddDelay(
        [poolObject]()
        {
            poolObject->mIsEnabled = false;
            poolObject->mIsVisible = false;
        },
        delayTime,
        &poolObject->OnDestroyEvent);
}

template <typename T>
void CGameObjectPool<T>::SetPoolObject(T* poolObject)
{
    this->mPoolObject = poolObject;
    this->Cleanup();
    this->Resize();
}

template <typename T>
void CGameObjectPool<T>::Cleanup()
{
    for (T* t : this->mListOfObjects)
    {
        delete t;
    }
    this->mListOfObjects.clear();
}

template <typename T>
void CGameObjectPool<T>::Resize()
{
    int prevSize = this->mListOfObjects.size();
    this->mListOfObjects.resize(this->mListOfObjects.size() + this->mResizeAmount);

    for (int i = prevSize; i < this->mListOfObjects.size(); i++)
    {
        this->mListOfObjects[i] = new T();
        this->mListOfObjects[i]->CopyFromOther(this->mPoolObject);
        this->mListOfObjects[i]->mIsEnabled = false;
        this->mListOfObjects[i]->mIsVisible = false;
    }
}