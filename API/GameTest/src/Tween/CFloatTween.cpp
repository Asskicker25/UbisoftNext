#include "CFloatTween.h"
#include "../Utilities/Lerp.h"

CFloatTween::CFloatTween(float startValue, float endValue, float time, std::function<void(float)> updateCallback) :
	mStartValue{ startValue },
	mEndValue{ endValue },
	mUpdateCallback{ updateCallback }
{
	mElapsedTime = 0;
	mTotalTime = time;
}

void CFloatTween::Update(float dt)
{
	mUpdateCallback(Lerp(mStartValue, mEndValue, mElapsedTime / mTotalTime));
}
