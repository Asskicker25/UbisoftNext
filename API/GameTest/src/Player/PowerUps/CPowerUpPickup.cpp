#include "CPowerUpPickup.h"
#include "../../Utilities/Random.h"
#include "../../Timer/CTimer.h"
#include "../../Entities/CPowerUpSpawner.h"


CPowerUpPickup::CPowerUpPickup(EPowerUp type) : CGameObject(), mPowerUpType{type}
{
	std::string path = "Assets/Sprites/";
	float x = 1;

	switch (mPowerUpType)
	{
	case NONE:
		break;
	case MAGNIFY:
		path += "Magnify.png";
		break;
	case DAMAGE_AMPLIFIER:
		path += "Fish_strip4.png";
		x = 4;
		 break;
	case EXPLOSIVE_IMPACT:
		path += "Bomb_strip10.png";
		x = 10;
		break;
	default:
		break;
	}

	pSprite = App::CreateSprite(path.c_str(), x, 1);

	mCurrentSpeed = GetRandomFloatNumber(mSpeedRange.x, mSpeedRange.y);

}

void CPowerUpPickup::Start()
{
	CGameObject::Start();
}

void CPowerUpPickup::Update()
{
	CGameObject::Update();

	float x, y;

	pSprite->GetPosition(x, y);

	y -= CTimer::GetInstance().mDeltaTime * mCurrentSpeed;

	pSprite->SetPosition(x, y);

	if (y <= 100)
	{
		mPowerUpSpawner->RemovePowerUp(this);
	}

}

void CPowerUpPickup::Render()
{
	CGameObject::Render();
}

void CPowerUpPickup::Cleanup()
{
	CGameObject::Cleanup();
}

void CPowerUpPickup::OnDestroy()
{
	CGameObject::OnDestroy();
}
