#pragma once

#include <vector>
#include "../Entities/CGameObject.h"

template <typename T>
class CObjectPool
{
public:
	virtual ~CObjectPool() {};
	virtual T* SpawnObject() = 0;
	virtual void DestroyObject(T*) = 0;
	virtual void DestroyObject(T*, float delayTime) = 0;
	virtual void SetPoolObject(T* poolObject);
	virtual void Resize() = 0;
	virtual void Cleanup();

	int mResizeAmount = 10;
	std::vector<T*> mListOfObjects;
	T* mPoolObject;

};



class CGameObjectPool : public CObjectPool<CGameObject>
{

public:
	// Inherited via CObjectPool
	CGameObject* SpawnObject() override;
	void DestroyObject(CGameObject* poolObject) override;
	void DestroyObject(CGameObject* poolObject, float delayTime) override;
	void SetPoolObject(CGameObject* poolObject) override;
	void Cleanup() override;
	void Resize() override;


};

