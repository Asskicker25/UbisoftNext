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
	virtual void Cleanup() = 0;						//Called after each level is done
	virtual void Shutdown() = 0;					//Called after quitting application
	virtual bool IsLevelComplete() = 0;

};

