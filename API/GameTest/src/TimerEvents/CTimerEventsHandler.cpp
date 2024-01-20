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
		currentEvent->Cleanup();
	}
}

void CTimerEventsHandler::Cleanup()
{
	while (mListOfEvents.size() != 0)
	{
		mListOfEvents[0]->Cleanup();
	}
}

void CTimerEventsHandler::AddDelay(std::function<void()> callback, float delayTime, CEvents* cleanUpEvent)
{
	CTimerEvents* newEvent = new CTimerEvents();

	newEvent->AssignEventData(callback, delayTime, cleanUpEvent);
	mListOfEvents.push_back(newEvent);

}

void CTimerEventsHandler::RemoveEvent(CTimerEvents* timerEvent)
{
	mListOfEvents.erase(std::remove(mListOfEvents.begin(), mListOfEvents.end(), timerEvent), mListOfEvents.end());

	delete timerEvent;
}
