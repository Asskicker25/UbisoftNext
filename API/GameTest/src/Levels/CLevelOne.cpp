#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

void CLevelOne::Start()
{
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
	mObjectPool.SetPoolObject(pPlayer);

	mCircleCollider = new CGameObject();
	mCircleCollider->mName = "Circle";
	mCircleCollider->pPhysicsShape = new CPhysicsShape(nullptr, CIRCLE);
	CPhysicsShapeCircle* circle = (CPhysicsShapeCircle*)mCircleCollider->pPhysicsShape->pShape;
	circle->SetCenter(700, 400);
	circle->SetRadius(20);

	mBoxCollider = new CGameObject();
	mBoxCollider->mName = "Box";
	mBoxCollider->pPhysicsShape = new CPhysicsShape(nullptr, BOX);
	CPhysicsShapeBox* box = (CPhysicsShapeBox*)mBoxCollider->pPhysicsShape->pShape;
	box->SetScale(100, 100);
	box->SetOffset(200, 400);

	mLineCollider = new CGameObject();
	mLineCollider->mName = "Line";
	mLineCollider->pPhysicsShape = new CPhysicsShape(nullptr, LINE);
	CPhysicsShapeLine* line = (CPhysicsShapeLine*)mLineCollider->pPhysicsShape->pShape;
	line->SetLine(200, 600, 700, 600);

}

void CLevelOne::Update()
{
	HandleInput();

	if (pPlayer == nullptr) return;

	mCollisionMessage = "";

	std::vector<CGameObject*> collidedObjects;

	if (CheckCollisionWithTag(pPlayer->pPhysicsShape, "Untagged", collidedObjects))
	{
		for (CGameObject* gameObject : collidedObjects)
		{
			mCollisionMessage += gameObject->mName + " | ";
		}
	}

	pPlayer->Update();
}

void CLevelOne::Render()
{
	if (pPlayer == nullptr) return;

	pPlayer->Render();

	App::Print(10, 100, ("Collision : " + mCollisionMessage).c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
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
		mObjectPool.DestroyObject(mObjectPool.SpawnObject(), 3.0f);
	}
}

