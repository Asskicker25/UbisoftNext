#include "CLevelOne.h"
#include "../Physics/Physics_Utils.h"
#include "../Physics/Shapes/CPhysicsShapeLine.h"

void CLevelOne::Start()
{
	pPlayer = new CPlayer();
	pPlayer->pSprite->SetPosition(400, 400);
	mObjectPool.SetPoolObject(pPlayer);
	pPlayer->mIsEnabled = true;

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
	mRaycastMessage = "";

	std::vector<CGameObject*> collidedObjects;

	if (CheckCollisionWithTag(pPlayer->pPhysicsShape, "Untagged", collidedObjects))
	{
		for (CGameObject* gameObject : collidedObjects)
		{
			mCollisionMessage += gameObject->mName + " | ";
		}
	}

	float x, y;
	pPlayer->pSprite->GetPosition(x, y);

	std::vector<CGameObject*> rayCastObjects;

	if (RaycastWithTag("Untagged", Vector2(x, y), Vector2(0, 1), 200, rayCastObjects))
	{
		for (CGameObject* gameObject : rayCastObjects)
		{
			mRaycastMessage += gameObject->mName + " | ";
		}
	}
	
}

void CLevelOne::Render()
{
	if (pPlayer == nullptr) return;

	App::Print(10, 100, ("Collision : " + mCollisionMessage).c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
	App::Print(10, 110, ("Raycast : " + mRaycastMessage).c_str(), 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CLevelOne::Cleanup()
{
	mIsLevelCompleted = false;
	mObjectPool.Cleanup();

	if (pPlayer == nullptr) return;
	pPlayer->Cleanup();
	pPlayer = nullptr;

	mCircleCollider->Cleanup();
	mBoxCollider->Cleanup();
	mLineCollider->Cleanup();
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

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		pPlayer->Destroy();
		pPlayer = nullptr;
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true))
	{
		pPlayer->mOpacity -= 0.1f;
		
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		mObjectPool.DestroyObject(mObjectPool.SpawnObject(), 3.0f);
	}
}

