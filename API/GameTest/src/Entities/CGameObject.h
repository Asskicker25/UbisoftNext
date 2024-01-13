#pragma once

#include "../EntityManager/CEntity.h"

class CGameObject : public CEntity
{

public:

	CSimpleSprite* sprite = nullptr;

	CGameObject();
	~CGameObject();

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void Destroy() override;
	void OnDestroy() override;
};

