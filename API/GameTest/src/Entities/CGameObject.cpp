#include "CGameObject.h"
#include "../EntityManager/CEntityManager.h"
#include "../Timer/CTimer.h"

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
	delete pSprite;
	delete pPhysicsShape;
}

void CGameObject::Start()
{
}

void CGameObject::Update()
{
	pSprite->Update(CTimer::GetInstance().deltaTime);
}

void CGameObject::Render()
{
	if (!mIsVisible) return;

	pSprite->Draw();
	pPhysicsShape->Render();

	App::Print(10, 70, "GameObject Render", 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameObject::Cleanup()
{
	delete this;
}

void CGameObject::OnDestroy()
{
	Cleanup();
}

void CGameObject::CopyFromOther(CGameObject* other)
{
	CEntity::CopyFromOther(other);
	
	if (pSprite != nullptr) { delete pSprite; }

	pSprite = new CSimpleSprite(other->pSprite);

}
