#include "Events.h"

void CEvents::Invoke()
{
	std::map<std::string, EventHandler>::iterator it;
	for (it = mListOfEvents.begin(); it != mListOfEvents.end(); ++it)
	{
		it->second();
	}
}

void CEvents::Subscribe(const std::string& eventName, EventHandler event)
{
	mListOfEvents[eventName] = event;
}

void CEvents::UnSubscribe(const std::string& eventName)
{
	mListOfEvents.erase(eventName);
}
