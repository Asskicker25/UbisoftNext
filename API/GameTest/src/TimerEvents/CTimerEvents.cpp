#include "CTimerEvents.h"
#include "../Timer/CTimer.h"
#include "CTimerEventsHandler.h"

CTimerEvents::CTimerEvents()
{
	mCurrentTime = 0;
}

void CTimerEvents::AssignEventData(std::function<void()> callback, float delayTime, CEvents* cleanUpEvent)
{
	this->mCallback = callback;
	this->mDelayTime = delayTime;

	if (cleanUpEvent == nullptr) return;

	cleanUpEvent->Subscribe("TimerEventCleanup", [this]()
		{
			Cleanup();
		});
}



void CTimerEvents::Update()
{
	mCurrentTime += CTimer::GetInstance().mDeltaTime / 1000.0f;

	if (mCurrentTime >= mDelayTime)
	{
		mCallback();
		mIsCompleted = true;

		if (mCleanUpEvent != nullptr)
		{
			mCleanUpEvent->UnSubscribe("TimerEventCleanup");
		}
	}

}

void CTimerEvents::Cleanup()
{
	CTimerEventsHandler::GetInstance().RemoveEvent(this);
}

bool CTimerEvents::IsComplete()
{
	return mIsCompleted;
}
