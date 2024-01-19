#include "CPlayerController.h"
#include "../Timer/CTimer.h"
#include "CPlayer.h"

CPlayerController::CPlayerController(CPlayer* player, int& controllerID) 
	: pPlayer{ player }, mControllerID { controllerID }
{
	bulletFactory = new BulletFactory();
}

CPlayerController::~CPlayerController()
{
}

void CPlayerController::Update()
{
	HandleInput();
	HandleRayCast();
	HandleMove();
	HandleCollision();
	//HandleRotation();
	HandleAnimation();

	mLastMoveDir = mMoveDir;
}

void CPlayerController::Render()
{
	if (!mIsEnabled) return;

	std::string animStateText = "Anim State : " + mAnimStateText;

	float x, y;
	pPlayer->pSprite->GetPosition(x, y);

	float ex, ey;

	ex = x + mMoveDir.x * mRayCastDistance;
	ey = y + mMoveDir.y * mRayCastDistance;

	App::DrawLine(x, y, ex, ey, 1, 0, 0);
	App::Print(10, 90, animStateText.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CPlayerController::HandleInput()
{
	if (!mIsEnabled) return;

	mMoveDir.x = App::GetController(mControllerID).GetLeftThumbStickX();
	mMoveDir.y = App::GetController(mControllerID).GetLeftThumbStickY();

	mMoveDir.Normalize();


	if (App::GetController(mControllerID).CheckButton(XINPUT_GAMEPAD_A, true))
	{
		ShootNormalBullet();
	}

}

void CPlayerController::HandleRayCast()
{
	if (!mIsEnabled) return;

	float x, y;
	pPlayer->pSprite->GetPosition(x, y);

	std::vector<CGameObject*> rayCastObjects;

	mCanMove = true;

	if (RaycastWithTag("Wall", Vector2(x, y), mMoveDir, mRayCastDistance, rayCastObjects))
	{
		mCanMove = false;
	}

}

void CPlayerController::HandleMove()
{
	if (!mIsEnabled) return;

	if (!mCanMove) return;

	if (mMoveDir.Magnitude() > 0.3f)
	{
		float x, y;
		pPlayer->pSprite->GetPosition(x, y);

		x += mMoveDir.x * mMoveSpeed * CTimer::GetInstance().mDeltaTime;
		y += mMoveDir.y * mMoveSpeed * CTimer::GetInstance().mDeltaTime;

		pPlayer->pSprite->SetPosition(x, y);
	}
	
}

void CPlayerController::HandleCollision()
{
	std::vector<CGameObject*> collidedObjects;

	if (CheckCollisionWithTag(pPlayer->pPhysicsShape, "Pickup", collidedObjects))
	{
		for (CGameObject* pickup : collidedObjects)
		{
			mMoveSpeed +=  0.2f;
			pickup->Destroy();
		}
	}
}

void CPlayerController::HandleRotation()
{
	if (!mIsEnabled) return;

	if (mMoveDir.Magnitude() > 0.3f)
	{
		if (mMoveDir.x > 0)
		{
			pPlayer->pSprite->SetScale(1.0f);
		}
		else if (mMoveDir.x < 0)
		{
			pPlayer->pSprite->SetScale(-1.0f);
		}
	}
}

void CPlayerController::HandleAnimation()
{
	if (!mIsEnabled) return;
	
	if (mMoveDir.Magnitude() > 0.3f)
	{
		if (mMoveDir.x > 0)
		{
			pPlayer->pSprite->SetAnimation(WALK_RIGHT);
			mFaceDir = 1;
			mAnimStateText = "WALK_RIGHT";
		}
		else if (mMoveDir.x < 0)
		{
			pPlayer->pSprite->SetAnimation(WALK_LEFT);
			mFaceDir = -1;
			mAnimStateText = "WALK_LEFT";
		}
		else
		{
			if (mFaceDir == 1)
			{
				pPlayer->pSprite->SetAnimation(WALK_RIGHT);
				mAnimStateText = "WALK_RIGHT";
			}
			else
			{
				pPlayer->pSprite->SetAnimation(WALK_LEFT);
				mAnimStateText = "WALK_LEFT";
			}
		}
	}
	else 
	{
		if (mMoveDir.x == 0 && mMoveDir.y == 0)
		{
			if (mFaceDir == 1)
			{
				pPlayer->pSprite->SetAnimation(IDLE_RIGHT);
				mAnimStateText = "IDLE_RIGHT";
			}
			else if (mFaceDir == -1)
			{
				pPlayer->pSprite->SetAnimation(IDLE_LEFT);
				mAnimStateText = "IDLE_LEFT";
			}
		}
	}
}

void CPlayerController::ShootNormalBullet()
{
	BaseBullet* bullet =  bulletFactory->CreateBullet(NORMAL);

	float x, y;
	pPlayer->pSprite->GetPosition(x, y);

	x += mMoveDir.x * mRayCastDistance;
	y += mMoveDir.y * mRayCastDistance;
	bullet->pSprite->SetPosition(x, y);

	bullet->mMoveDir = mMoveDir;


}
