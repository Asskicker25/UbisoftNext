#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"

void CLevelOne::Start()
{	
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
	mObjectPool.SetPoolObject(pPlayer);

	collider = new CGameObject();
	collider->pPhysicsShape = new CPhysicsShape(nullptr,CIRCLE);
	CPhysicsShapeCircle* circle = (CPhysicsShapeCircle*)collider->pPhysicsShape->pShape;
	circle->SetCenter(700, 400);
	circle->SetRadius(20);
}

void CLevelOne::Update()
{
	HandleInput();

	if (pPlayer == nullptr) return;

	isColliding = CheckCollision(*pPlayer->pPhysicsShape, *collider->pPhysicsShape);

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

