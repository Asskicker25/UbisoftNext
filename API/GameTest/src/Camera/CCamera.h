#pragma once
#include "../../App/DataClasses.h"

class CCamera
{
public:

	static CCamera& GetInstance();

	CCamera();

	Vector2 mCameraPosition;

};

