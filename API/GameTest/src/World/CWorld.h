#pragma once
#include "../../App/DataClasses.h"

class CWorld
{
public:

	static CWorld& GetInstance();

	CWorld();

	Vector2 mOrigin;

};

