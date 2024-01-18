#pragma once

#include <functional>
#include "../Events/Events.h"

class CTimerEvents
{

public:

	float mDelayTime = 0;

	std::function<void()> mCallback = nullptr;
	CEvents* mCleanUpEvent = nullptr;

	CTimerEvents();

	void AssignEventData(std::function<void()> callback, float delayTime, CEvents* cleanUpEvent);

	void Update();
	void Cleanup();
	bool IsComplete();


private:
	bool mIsCompleted = false;
	float mCurrentTime = 0;

};

