#pragma once

#include "../Entities/CGameObject.h"
#include "CPlayerController.h"

enum EPlayerAnimState
{
	IDLE_RIGHT = 0,
	IDLE_LEFT = 1,
	WALK_RIGHT = 2,
	WALK_LEFT = 3
};

class CPlayer : public CGameObject
{
public:

	CPlayer();

	void Start() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
	void OnDestroy() override;

private:

	class Pimpl;
	Pimpl* pimpl;

	CPlayerController* pPlayerController = nullptr;
};

