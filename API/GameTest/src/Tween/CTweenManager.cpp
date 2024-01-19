#include "CTweenManager.h"
#include "../Timer/CTimer.h"

CTweenManager& CTweenManager::GetInstance()
{
	static CTweenManager instance;
	return instance;
}

void CTweenManager::Update()
{
	std::vector<CBaseTween*> removableTweens;

	for (CBaseTween* tween : mListOfTweens)
	{
		float deltaTime = CTimer::GetInstance().mDeltaTime;
		tween->mElapsedTime += deltaTime;
		tween->Update(deltaTime);

		if (tween->mElapsedTime >= tween->mTotalTime)
		{
			if (tween->mOnComplete != nullptr)
			{
				tween->mOnComplete();
			}
			removableTweens.push_back(tween);
		}
	}

	for (CBaseTween* tween : removableTweens)
	{
		mListOfTweens.erase(std::remove(mListOfTweens.begin(), mListOfTweens.end(), tween), mListOfTweens.end());
		delete tween;
	}
}

void CTweenManager::Cleanup()
{
	while (mListOfTweens.size() != 0)
	{
		CBaseTween* tween = mListOfTweens[0];
		mListOfTweens.erase(mListOfTweens.begin());
		delete tween;
	}
}

void CTweenManager::AddFloatTween(float startValue, float endValue, float time, std::function<void(float)> updateCallback)
{
	CFloatTween* tween = new CFloatTween(startValue, endValue, time, updateCallback);

	mListOfTweens.push_back(tween);
}

