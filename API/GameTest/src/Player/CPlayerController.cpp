#include "CPlayerController.h"
#include "../Timer/CTimer.h"
#include "CPlayer.h"

CPlayerController::CPlayerController(CPlayer* player, int& controllerID) 
	: pPlayer{ player }, mControllerID { controllerID }
{
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

	Vector2 pos = pPlayer->GetPosition();

	float ex, ey;

	ex = pos.x + mMoveDir.x * mRayCastDistance;
	ey = pos.y + mMoveDir.y * mRayCastDistance;

	App::DrawLine(pos.x, pos.y, ex, ey, 1, 0, 0);
	App::Print(10, 90, animStateText.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
	App::Print(10, 70, mCollisionDetails.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

}

void CPlayerController::HandleInput()
{
	if (!mIsEnabled) return;

	mMoveDir.x = App::GetController(mControllerID).GetLeftThumbStickX();
	mMoveDir.y = App::GetController(mControllerID).GetLeftThumbStickY();

	mMoveDir.Normalize();


	if (App::GetController(mControllerID).CheckButton(XINPUT_GAMEPAD_A, true))
	{
	}

}

void CPlayerController::HandleRayCast()
{
	if (!mIsEnabled) return;

	Vector2 pos = pPlayer->GetPosition();

	std::vector<CGameObject*> rayCastObjects;

	mCanMove = true;

	if (RaycastWithTag("Untagged", pos, mMoveDir, mRayCastDistance, rayCastObjects))
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
	mCollisionDetails = "Collision : ";

	std::vector<CGameObject*> collidedObjects;

	if (CheckCollisionWithTag(pPlayer->pPhysicsShape, "Untagged", collidedObjects))
	{
		for (CGameObject* object : collidedObjects)
		{
			mCollisionDetails += object->mName + " | ";
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


