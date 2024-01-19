#pragma once

#include "../../Entities/CGameObject.h"

class CPickUp : public CGameObject
{
public:
	CPickUp();

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

	// CopyFromOther - Copies data from another game object.
	// Parameters:
	//   other - A pointer to the game object to copy properties from.
	void CopyFromOther(CGameObject* other) override;
};