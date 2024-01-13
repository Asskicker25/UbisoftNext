#include "CTimer.h"

CTimer& CTimer::GetInstance()
{
	static CTimer instance;
	return instance;
}
