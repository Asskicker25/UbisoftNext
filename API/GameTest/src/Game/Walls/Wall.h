#pragma once

#include "../../Entities/CGameObject.h"

class CWall : public CGameObject
{
public:
	CWall();

	// Inherited via CEntity
	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

	// CopyFromOther - Copies data from another game object.
	// Parameters:
	//   other - A pointer to the game object to copy properties from.
	virtual void CopyFromOther(CGameObject* other);
};

