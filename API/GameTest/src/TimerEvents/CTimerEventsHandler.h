#pragma once

#include <functional>
#include <vector>
#include "../Events/Events.h"

#include "CTimerEvents.h"

class CTimerEventsHandler
{
public:

	static CTimerEventsHandler& GetInstance();

	void Start();
	void Update();
	void Cleanup();
	
	void AddDelay(std::function<void()> callback, float delayTime = 0, CEvents* cleanUpEvent = nullptr);
	void RemoveEvent(CTimerEvents* timerEvent);

private:

	std::vector<CTimerEvents*> mListOfEvents;
};

