#pragma once
#include "../CBasePowerUp.h"


class CExplosiveImpact : public CBasePowerUp
{
public:
	CExplosiveImpact();

	// Inherited via CBasePowerUp
	void Activate() override;
	void Deactivate() override;
};

