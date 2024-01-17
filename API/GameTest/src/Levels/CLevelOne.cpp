#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"

void CLevelOne::Start()
{	
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
	mObjectPool.SetPoolObject(pPlayer);

	mCircleCollider = new CGameObject();
	mCircleCollider->pPhysicsShape = new CPhysicsShape(nullptr,CIRCLE);
	CPhysicsShapeCircle* circle = (CPhysicsShapeCircle*)mCircleCollider->pPhysicsShape->pShape;
	circle->SetCenter(700, 400);
	circle->SetRadius(20);

	mBoxCollider = new CGameObject();
	mBoxCollider->pPhysicsShape = new CPhysicsShape(nullptr, BOX);
	CPhysicsShapeBox* box = (CPhysicsShapeBox*)mBoxCollider->pPhysicsShape->pShape;
	box->SetScale(100, 100);
	box->SetOffset(200, 400);
	
}

void CLevelOne::Update()
{
	HandleInput();

	if (pPlayer == nullptr) return;

	isColliding = CheckCollision(*pPlayer->pPhysicsShape, *mCircleCollider->pPhysicsShape);

	if (!isColliding)
	{
		isColliding = CheckCollision(*pPlayer->pPhysicsShape, *mBoxCollider->pPhysicsShape);
	}

	pPlayer->Update();
}

void CLevelOne::Render()
{
	if (pPlayer == nullptr) return;

	pPlayer->Render();

	if (isColliding)
	{
		App::Print(10, 100, "Collision", 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
	}
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;
	mObjectPool.Cleanup();

	if (pPlayer == nullptr) return;
	pPlayer->Cleanup();
}

void CLevelOne::Shutdown()
{
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

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		pPlayer->Destroy();
		pPlayer = nullptr;
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		mObjectPool.DestroyObject( mObjectPool.SpawnObject(), 3.0f);
	}
}

