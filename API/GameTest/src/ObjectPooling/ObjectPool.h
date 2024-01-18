#pragma once

#include <vector>
#include "../Entities/CGameObject.h"

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


// Specialized object pool for CGameObject instances.
class CGameObjectPool : public CObjectPool<CGameObject>
{

public:
	// Inherited via CObjectPool
	 CGameObject* SpawnObject() override;  // Creates and returns a new CGameObject from the pool.
    void DestroyObject(CGameObject* poolObject) override;  // Marks a CGameObject as inactive in the pool.
    void DestroyObject(CGameObject* poolObject, float delayTime) override;  // Marks an object as inactive with a delay before reusing it.
    void SetPoolObject(CGameObject* poolObject) override;  // Assigns a prototype CGameObject to the pool for initialization.
    void Cleanup() override;  // Cleans up resources and resets the CGameObject pool.
    void Resize() override;  // Adjusts the size of the CGameObject pool.
};


