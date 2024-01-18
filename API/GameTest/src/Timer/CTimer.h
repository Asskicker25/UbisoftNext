#pragma once

class CTimer
{
public:

	static CTimer& GetInstance();

	float mDeltaTime = 0;
	float mGameTime = 0;
};

