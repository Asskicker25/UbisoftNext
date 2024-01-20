#include "CPlayer.h"
#include "../Physics/Physics_Utils.h"
#include "PowerUps/Types/CDamageAmplifier.h"
#include "PowerUps/Types/CExplosiveImpact.h"
#include "PowerUps/Types/CMegaMagnify.h"

class CPlayer::Pimpl
{
public:
	Pimpl(CPlayer* player) : mPlayer{ player } {};

	CPlayer* mPlayer = nullptr;

};

CPlayer::CPlayer(const std::string& spritePath, int controllerID) :
	pimpl{ new Pimpl(this) }
{

	mTotalHealth = mMaxHealth;
	mTag = "Player";

	pSprite = App::CreateSprite(spritePath.c_str(), 35, 1);
	//pSprite = App::CreateSprite("Assets/Sprites/Cat_strip35.png", 35, 1);
	float speed = 1.0f / 6.0f;

	pSprite->CreateAnimation(IDLE, speed, { 0,1,2,3 });
	pSprite->CreateAnimation(AIM, speed, { 5 });
	pSprite->CreateAnimation(THROW, speed, {  6, 7, 8, 9 });
	pSprite->CreateAnimation(TAUNT, speed, { 10, 11, 12, 13, 14, 15 });
	pSprite->CreateAnimation(HIT_ONE, speed, { 16, 17, 18, 19, 20 });
	pSprite->CreateAnimation(HIT_TWO, speed, { 21, 22, 23 });
	pSprite->CreateAnimation(DEATH, speed, { 24, 25, 26, 27, 28, 29, 30, 31, 32 });
		
	pPhysicsShape = new CPhysicsShape(this, BOX);
	pPhysicsShape->pShape->SetScale(0.2f, 0.4f);
	pPhysicsShape->pShape->SetOffset(0,- 117/3 );

	pSprite->SetAnimation(IDLE);

	mMegaMagnify.first = new CMegaMagnify();
	mDamageAmplifier.first = new CDamageAmplifier();
	mExplosiveImpact.first = new CExplosiveImpact();

	mMegaMagnify.second = 2;
	mDamageAmplifier.second = 1;
	mExplosiveImpact.second = 1;

	pSprite->SetScale(0.5f);

}

void CPlayer::Start()
{
}

void CPlayer::Update()
{

	CGameObject::Update();
}

void CPlayer::Render()
{
	CGameObject::Render();
}

void CPlayer::Cleanup()
{
	CGameObject::Cleanup();
}

void CPlayer::OnDestroy()
{
	CGameObject::OnDestroy();
}

void CPlayer::ReduceHealth(int reduceAmount)
{
	mTotalHealth -= reduceAmount;

	if (mTotalHealth < 0) { mTotalHealth = 0; }
}

bool CPlayer::IsPlayerDead()
{
	return mTotalHealth <= 0;
}

