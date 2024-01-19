#pragma once

#include "CBaseTween.h"

class CFloatTween : public CBaseTween
{
public:
	
	CFloatTween(float startValue, float endValue, float time, std::function<void(float)> updateCallback = nullptr);

	// Inherited via CBaseTween
	void Update(float dt) override;

	float mStartValue = 0;
	float mEndValue = 0;

	std::function<void(float)> mUpdateCallback;
};

