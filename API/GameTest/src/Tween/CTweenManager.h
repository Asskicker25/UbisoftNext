#pragma once

#include "CFloatTween.h"
#include <vector>

class CTweenManager
{
public:

	static CTweenManager& GetInstance();

	void Update();
	void Cleanup();

	void AddFloatTween(float startValue, float endValue, float time, std::function<void(float)> updateCallback);

private:
	std::vector<CBaseTween*> mListOfTweens;
};

