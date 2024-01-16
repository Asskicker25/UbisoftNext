#include "CTimerEventsHandler.h"

CTimerEventsHandler& CTimerEventsHandler::GetInstance()
{
	static CTimerEventsHandler instance;
	return instance;
}

void CTimerEventsHandler::Start()
{
}

void CTimerEventsHandler::Update()
{
	std::vector<CTimerEvents*> eventsToRemove;

	for (CTimerEvents* currentEvent : mListOfEvents)
	{
		if (currentEvent->IsComplete())
		{
			eventsToRemove.push_back(currentEvent);
			continue;
		}

		currentEvent->Update();
	}

	for (CTimerEvents* currentEvent : eventsToRemove)
	{
		mListOfEvents.erase(std::remove(mListOfEvents.begin(), mListOfEvents.end(), currentEvent), mListOfEvents.end());
		currentEvent->Cleanup();
		delete currentEvent;
	}
}

void CTimerEventsHandler::Cleanup()
{
	while (mListOfEvents.size() != 0)
	{
		mListOfEvents[0]->Cleanup();
		delete mListOfEvents[0];
		mListOfEvents.erase(mListOfEvents.begin());
	}
}

void CTimerEventsHandler::AddDelay(std::function<void()> callback, float delayTime)
{
	CTimerEvents* newEvent = new CTimerEvents();

	newEvent->mDelayTime = delayTime;
	newEvent->mCallback = callback;
	mListOfEvents.push_back(newEvent);

}
