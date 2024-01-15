#pragma once

#include <vector>
#include "../Entities/CGameObject.h"

template <typename T>
class CObjectPool
{
public:
	virtual ~CObjectPool() {};
	virtual T* SpawnObject() = 0;
	virtual T* DestroyObject() = 0;
	virtual void SetPoolObject(T* poolObject);

	int mResizeAmount = 10;

private:
	void Resize();


	T* mPoolObject;
	std::vector<T*> mListOfObjects;

};



class CGameObjectPool : public CObjectPool<CGameObject>
{

public:
	// Inherited via CObjectPool
	CGameObject* SpawnObject() override;
	CGameObject* DestroyObject() override;
	void SetPoolObject(CGameObject* poolObject) override;

};

