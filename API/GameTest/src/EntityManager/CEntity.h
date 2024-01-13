#pragma once

#include <unordered_map>
#include <string>
#include "../../App/app.h"

class CEntity
{
public:

	CEntity();
	virtual ~CEntity();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
	virtual void Destroy() = 0;
	virtual void OnDestroy() = 0;

	virtual void InitializeEntity(CEntity* entity);

	std::string mEntityId = "";
	bool mIsEnabled = true;
	bool mIsStartInvoked = false;
};

