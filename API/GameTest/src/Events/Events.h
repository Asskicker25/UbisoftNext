#pragma once

#include <functional>
#include <map>
#include <string>

class CEvents
{
public:
	using EventHandler = std::function<void()>;
	void Invoke();
	void Subscribe(const std::string& eventName, EventHandler event);
	void UnSubscribe(const std::string& eventName);

private:
	std::map<std::string, EventHandler> mListOfEvents;
};

