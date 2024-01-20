#pragma once
#include "../CBasePowerUp.h"

class CMegaMagnify :public CBasePowerUp
{
public: 
	CMegaMagnify();

	// Inherited via CBasePowerUp
	void Activate() override;
	void Deactivate() override;

private:
	float mMagnifyScale = 3;
};

