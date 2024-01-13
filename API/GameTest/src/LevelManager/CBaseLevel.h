#pragma once

#include "../../App/app.h"
#include "../Entities/CGameObject.h"

class CBaseLevel
{

public:

	virtual ~CBaseLevel() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
	virtual bool IsLevelComplete() = 0;

};

