#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

#include "../EntityManager/CEntityManager.h"

#include "../World/CWorld.h"
#include "../Player/CPlayerManager.h"
#include "../Entities/CGameplayManager.h"
#include "../Tween/CTweenManager.h"

#include "../Environment/Wall/CWall.h"
#include "../Environment/Ground/CGround.h"
#include "../Player/Arc/CArcDot.h"

#include "../ParticleSystem/CParticleSystem.h"

void CLevelOne::Start()
{

	CWorld::GetInstance().mOrigin = Vector2(-522, 0);

	wall1 = new CWall();
	wall1->SetPosition(0, 600, true);
	wall1->mYRange = Vector2(400, 700);

	wall2 = new CWall();
	wall2->SetPosition(0, 300, true);
	wall2->mYRange = Vector2(100, 350);


	mEnvironmentObjects.push_back(wall1);
	mEnvironmentObjects.push_back(wall2);

	CGameplayManager::GetInstance().OnTurnStart.Subscribe("Level_TurnStart", [this]()
		{
			HandleCameraMovement(true);
		});

	CPlayerManager::GetInstance().OnShoot.Subscribe("Level_Shoot", [this]()
		{
			HandleOnShoot();
		});


	CPlayerManager::GetInstance().Start();
	CGameplayManager::GetInstance().Start();

	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileFail.Subscribe("Player_Fail", [this]()
		{
			HandleCameraMovement(false);
		});

	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileSuccess.Subscribe("Player_Fail", [this]()
		{
			HandleCameraMovement(false);
		});

	CPlayerManager::GetInstance().OnPlayerDead.Subscribe("Level_Complete", [this]()
		{
			mIsLevelCompleted = true;
		});

	HandleEnvironmentCreations();

	CEntityManager::GetInstance().SortEntities();
}

void CLevelOne::Update()
{
	HandleInput();
	HandleCameraFollow();
	CGameplayManager::GetInstance().Update();
	CPlayerManager::GetInstance().Update();
}

void CLevelOne::Render()
{
	std::string message = std::to_string(CWorld::GetInstance().mOrigin.x) + " , " + std::to_string(CWorld::GetInstance().mOrigin.y);

	App::Print(10, 110, message.c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);

	CGameplayManager::GetInstance().Render();
	CPlayerManager::GetInstance().Render();
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;

	while (mEnvironmentObjects.size() != 0)
	{
		CGameObject* obj = mEnvironmentObjects[0];
		mEnvironmentObjects.erase(mEnvironmentObjects.begin());

		obj->Cleanup();
	}

	
	CGameplayManager::GetInstance().OnTurnStart.UnSubscribe("Level_TurnStart");
	CPlayerManager::GetInstance().OnShoot.UnSubscribe("Level_Shoot");
	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileFail.UnSubscribe("Player_Fail");
	CPlayerManager::GetInstance().pProjectileFactory->OnProjectileSuccess.UnSubscribe("Player_Fail");
	CGameplayManager::GetInstance().OnWallSwitch.UnSubscribe("Wall_Switch");
	CPlayerManager::GetInstance().Cleanup();
	CGameplayManager::GetInstance().Cleanup();

}

bool CLevelOne::IsLevelComplete()
{
	return mIsLevelCompleted;
}

void CLevelOne::HandleInput()
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		mIsLevelCompleted = true;
	}

	//mCanCameraMove = App::GetController().CheckButton(XINPUT_GAMEPAD_A, false);

	if (!mCanCameraMove) return;

	mCameraMoveDir.x = App::GetController().GetLeftThumbStickX();
	mCameraMoveDir.y = App::GetController().GetLeftThumbStickY();

	mCameraMoveDir.Normalize();

	CWorld::GetInstance().mOrigin.x += mCameraMoveDir.x * 20;
	CWorld::GetInstance().mOrigin.y += mCameraMoveDir.y * 20;
}


void CLevelOne::HandleEnvironmentCreations()
{

	

	CGameplayManager::GetInstance().OnWallSwitch.Subscribe("Wall_Switch", [this]()
		{
			wall1->ChangePosition();
			wall2->ChangePosition();
		});



	float windowCenterX = APP_VIRTUAL_WIDTH * 0.5f;
	float windowCenterY = APP_VIRTUAL_HEIGHT * 0.5f;

	CGameObject* bg1 = new CGameObject();
	bg1->pSprite = App::CreateSprite("Assets/Sprites/BG1.png", 1, 1);
	bg1->mOrder = -5;
	bg1->mIsUI = true;
	bg1->SetPosition(windowCenterX, windowCenterY, true);

	CGameObject* bg2 = new CGameObject();
	bg2->pSprite = App::CreateSprite("Assets/Sprites/BG2.png", 1, 1);
	bg2->pSprite->SetColor(0.9f, 0.9f, 0.9f);
	bg2->mOrder = -4;
	bg2->mIsUI = true;
	bg2->SetPosition(windowCenterX, windowCenterY, true);

	CGameObject* bg3 = new CGameObject();
	bg3->pSprite = App::CreateSprite("Assets/Sprites/BG3.png", 1, 1);
	bg3->mOrder = -3;
	bg3->mIsUI = true;
	bg3->SetPosition(windowCenterX, windowCenterY, true);

	mEnvironmentObjects.push_back(bg1);
	mEnvironmentObjects.push_back(bg2);
	mEnvironmentObjects.push_back(bg3);

	//Player 1 Side
	for (int i = -2; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CGround* ground1 = new CGround();

			if (j == 0 || i == -2)
			{
				ground1->pPhysicsShape = new CPhysicsShape(ground1, BOX);

			}
			else
			{
				ground1->pSprite->SetAnimation(4);
			}

			ground1->SetPosition(-600 - i * ground1->pSprite->GetWidth(), 160 - j * ground1->pSprite->GetHeight(), true);

			mEnvironmentObjects.push_back(ground1);


			if (i == -2 && j == 0)
			{
				ground1->pSprite->SetAnimation(2);
			}

			if (j == 0 && i != -2)
			{
				ground1->pSprite->SetAnimation(1);
			}

			if (j != 0 && i == -2)
			{
				ground1->pSprite->SetAnimation(5);
			}

		}
	}

	//Player 2 Side
	for (int i = -2; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CGround* ground1 = new CGround();

			if (j == 0 || i == -2)
			{
				ground1->pPhysicsShape = new CPhysicsShape(ground1, BOX);

			}
			else
			{
				ground1->pSprite->SetAnimation(4);
			}
			ground1->SetPosition(600 + i * ground1->pSprite->GetWidth(), 160 - j * ground1->pSprite->GetHeight(), true);

			mEnvironmentObjects.push_back(ground1);


			if (i == -2 && j == 0)
			{
				ground1->pSprite->SetAnimation(0);
			}

			if (j == 0 && i != -2)
			{
				ground1->pSprite->SetAnimation(1);
			}

			if (j != 0 && i == -2)
			{
				ground1->pSprite->SetAnimation(3);
			}

		}
	}

}

void CLevelOne::HandleCameraMovement(bool currentPlayer)
{

	wall1->pSprite->SetAnimation(CGameplayManager::GetInstance().mCurrentTurn == 1 ? 0 : 1);
	wall2->pSprite->SetAnimation(CGameplayManager::GetInstance().mCurrentTurn == 1 ? 0 : 1);

	float cameraValue;
	if (currentPlayer)
	{
		cameraValue = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -850 : -150;
	}
	else
	{
		cameraValue = CGameplayManager::GetInstance().mCurrentTurn == 1 ? -150 : -850;
	}

	CTweenManager::GetInstance().AddFloatTween(CWorld::GetInstance().mOrigin.x, cameraValue, mCameraMoveTime,
		[](float value)
		{
			CWorld::GetInstance().mOrigin.x = value;
		}
	);
}



void CLevelOne::HandleOnShoot()
{
	mCurrentProjectile = CPlayerManager::GetInstance().pProjectileFactory->GetCurrentProjectile();

	mOriginInitPos = CWorld::GetInstance().mOrigin;

	float x, y;

	mCurrentProjectile->pSprite->GetPosition(x, y);

	x -= mOriginInitPos.x;

	mProjectileLastPos = x;

	mCameraFollowProjectile = true;

}

void CLevelOne::HandleCameraFollow()
{

	if (!mCameraFollowProjectile) return;

	float x, y;

	mCurrentProjectile->pSprite->GetPosition(x, y);

	x -= mOriginInitPos.x;

	float mPosOffset = x - mProjectileLastPos;

	mProjectileLastPos = x;


	if (CGameplayManager::GetInstance().mCurrentTurn == 1)
	{
		if (x >= mWindowCenterX)
		{
			CWorld::GetInstance().mOrigin.x += mPosOffset;
		}
	}
	else
	{
		if (x <= mWindowCenterX)
		{
			CWorld::GetInstance().mOrigin.x += mPosOffset;
		}
	}

}