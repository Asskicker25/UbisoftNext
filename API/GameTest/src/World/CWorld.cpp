#include "CWorld.h"
#include "../../App/app.h"


CWorld& CWorld::GetInstance()
{
	static CWorld instance;
	return instance;
}

CWorld::CWorld()
{
}
