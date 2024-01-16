#include "CTimerEvents.h"
#include "../Timer/CTimer.h"

CTimerEvents::CTimerEvents()
{
	mCurrentTime = 0;
}

void CTimerEvents::Update()
{
	mCurrentTime += CTimer::GetInstance().deltaTime/ 1000.0f;

	if (mCurrentTime >= mDelayTime)
	{
		mCallback();
		mIsCompleted = true;
	}

}

void CTimerEvents::Cleanup()
{
}

bool CTimerEvents::IsComplete()
{
	return mIsCompleted;
}
