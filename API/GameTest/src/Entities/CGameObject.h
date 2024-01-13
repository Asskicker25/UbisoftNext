#pragma once

#include "../EntityManager/CEntity.h"

class CGameObject : public CEntity
{

public:

	CGameObject();

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void Destroy() override;
	void OnDestroy() override;
};

