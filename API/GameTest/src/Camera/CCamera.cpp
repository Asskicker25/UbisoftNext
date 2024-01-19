#include "CCamera.h"

CCamera& CCamera::GetInstance()
{
	static CCamera instance;
	return instance;
}

CCamera::CCamera()
{
}
