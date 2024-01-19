#pragma once

#include <functional>

class CBaseTween
{
public:
	virtual void Update(float dt) = 0;

	std::function<void()> mOnComplete = nullptr;

	float mTotalTime = 0;
	float mElapsedTime = 0;
};

