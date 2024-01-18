#include "CPlayer.h"
#include "../Physics/Physics_Utils.h"

class CPlayer::Pimpl
{
public:
	Pimpl(CPlayer* player) : mPlayer{ player } {};

	CPlayer* mPlayer = nullptr;

};

CPlayer::CPlayer() :
	pimpl{ new Pimpl(this) }
{

	pSprite = App::CreateSprite("Assets/Sprites/Batman_01_strip6.png", 12, 1);
	float speed = 1.0f / 3.0f;

	pSprite->CreateAnimation(IDLE_RIGHT, speed, { 0 });
	pSprite->CreateAnimation(IDLE_LEFT, speed, { 1 });
	pSprite->CreateAnimation(WALK_RIGHT, speed, { 2, 3, 4, 5, 6 });
	pSprite->CreateAnimation(WALK_LEFT, speed, { 7, 8, 9, 10, 11 });
		
	pPlayerController = new CPlayerController(this->pSprite);
	pPhysicsShape = new CPhysicsShape(this->pSprite, BOX);

}

void CPlayer::Start()
{
	pPlayerController->mIsEnabled = true;
}

void CPlayer::Update()
{
	pPlayerController->Update();

	CGameObject::Update();
}

void CPlayer::Render()
{
	std::string moveDirText = "Move Dir : " +
		std::to_string(pPlayerController->mMoveDir.x) + " , " + std::to_string(pPlayerController->mMoveDir.y);
	App::Print(10, 80, moveDirText.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	pPlayerController->Render();

	CGameObject::Render();
}

void CPlayer::Cleanup()
{
	pPlayerController->mIsEnabled = false;
	CGameObject::Cleanup();
}

void CPlayer::OnDestroy()
{
	CGameObject::OnDestroy();
}

