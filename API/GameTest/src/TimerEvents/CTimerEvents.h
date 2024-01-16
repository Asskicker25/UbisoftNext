#pragma once

#include <functional>

class CTimerEvents
{

public:

	float mDelayTime = 0;
	std::function<void()> mCallback = nullptr;

	CTimerEvents();
	void Update();
	void Cleanup();
	bool IsComplete();


private:
	bool mIsCompleted = false;
	float mCurrentTime = 0;

};

