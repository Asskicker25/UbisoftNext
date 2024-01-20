#pragma once

#include "../../Entities/CGameObject.h"

class CPowerUpUI : public CGameObject
{
public:

	CPowerUpUI();

	// Inherited via CEntity
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Cleanup();
	virtual void OnDestroy();

	void SetCount(int count);
	void SetVisibility(bool state, bool isSelected);

private:

	float mOffset = 20;

	CGameObject* mCount;
	CGameObject* mSelected;
};

