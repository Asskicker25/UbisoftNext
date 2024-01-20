#pragma once

#include "../CBasePowerUp.h"

class CDamageAmplifier : public CBasePowerUp
{
public:

	CDamageAmplifier();

	// Inherited via CBasePowerUp
	void Activate() override;
	void Deactivate() override;
};

