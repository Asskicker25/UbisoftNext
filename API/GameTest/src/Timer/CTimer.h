#pragma once

class CTimer
{
public:

	static CTimer& GetInstance();

	float deltaTime = 0;
};

