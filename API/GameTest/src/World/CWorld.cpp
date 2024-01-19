#include "CWorld.h"

CWorld& CWorld::GetInstance()
{
	static CWorld instance;
	return instance;
}

CWorld::CWorld()
{
}
