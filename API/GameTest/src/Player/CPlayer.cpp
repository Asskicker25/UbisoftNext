#include "CPlayer.h"
#include "../Physics/Physics_Utils.h"

class CPlayer::Pimpl
{
public:
	Pimpl(CPlayer* player) : mPlayer{ player } {};

	CPlayer* mPlayer = nullptr;

};

CPlayer::CPlayer(int controllerID) :
	pimpl{ new Pimpl(this) }
{
	mTag = "Player";

	pSprite = App::CreateSprite("Assets/Sprites/Cat_strip35.png", 35, 1);
	float speed = 1.0f / 6.0f;

	pSprite->CreateAnimation(IDLE, speed, { 0,1,2,3 });
	pSprite->CreateAnimation(AIM, speed, { 5 });
	pSprite->CreateAnimation(THROW, speed, {  6, 7, 8, 9 });
	pSprite->CreateAnimation(TAUNT, speed, { 10, 11, 12, 13, 14, 15 });
	pSprite->CreateAnimation(HIT_ONE, speed, { 16, 17, 18, 19, 20 });
	pSprite->CreateAnimation(HIT_TWO, speed, { 21, 22, 23 });
	pSprite->CreateAnimation(DEATH, speed, { 24, 25, 26, 27, 28, 29, 30, 31, 32 });
		
	pPhysicsShape = new CPhysicsShape(this, BOX);
	pPhysicsShape->pShape->SetScale(0.5f, 0.5f);
	pPhysicsShape->pShape->SetOffset(0,- 117/4 );

	pSprite->SetAnimation(IDLE);

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

