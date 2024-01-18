#include "CPlayerController.h"
#include "../Timer/CTimer.h"
#include "CPlayer.h"

CPlayerController::CPlayerController(CSimpleSprite* sprite) : pSprite{ sprite }
{
}

CPlayerController::~CPlayerController()
{
}

void CPlayerController::Update()
{
	HandleInput();
	HandleMove();
	//HandleRotation();
	HandleAnimation();

	mLastMoveDir = mMoveDir;
}

void CPlayerController::Render()
{
	if (!mIsEnabled) return;

	std::string animStateText = "Anim State : " + mAnimStateText;


	App::Print(10, 90, animStateText.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CPlayerController::HandleInput()
{
	if (!mIsEnabled) return;

	mMoveDir.x = App::GetController().GetLeftThumbStickX();
	mMoveDir.y = App::GetController().GetLeftThumbStickY();

	mMoveDir.Normalize();

}

void CPlayerController::HandleMove()
{
	if (!mIsEnabled) return;

	if (mMoveDir.Magnitude() > 0.3f)
	{
		float x, y;
		pSprite->GetPosition(x, y);

		x += mMoveDir.x * mMoveSpeed * CTimer::GetInstance().mDeltaTime;
		y += mMoveDir.y * mMoveSpeed * CTimer::GetInstance().mDeltaTime;

		pSprite->SetPosition(x, y);
	}
	
}

void CPlayerController::HandleRotation()
{
	if (!mIsEnabled) return;

	if (mMoveDir.Magnitude() > 0.3f)
	{
		if (mMoveDir.x > 0)
		{
			pSprite->SetScale(1.0f);
		}
		else if (mMoveDir.x < 0)
		{
			pSprite->SetScale(-1.0f);
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
			pSprite->SetAnimation(WALK_RIGHT);
			mFaceDir = 1;
			mAnimStateText = "WALK_RIGHT";
		}
		else if (mMoveDir.x < 0)
		{
			pSprite->SetAnimation(WALK_LEFT);
			mFaceDir = -1;
			mAnimStateText = "WALK_LEFT";
		}
		else
		{
			if (mFaceDir == 1)
			{
				pSprite->SetAnimation(WALK_RIGHT);
				mAnimStateText = "WALK_RIGHT";
			}
			else
			{
				pSprite->SetAnimation(WALK_LEFT);
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
				pSprite->SetAnimation(IDLE_RIGHT);
				mAnimStateText = "IDLE_RIGHT";
			}
			else if (mFaceDir == -1)
			{
				pSprite->SetAnimation(IDLE_LEFT);
				mAnimStateText = "IDLE_LEFT";
			}
		}
	}
}
