#include "CGameObject.h"
#include "../EntityManager/CEntityManager.h"
#include "../Timer/CTimer.h"

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
	delete sprite;
}

void CGameObject::Start()
{
}

void CGameObject::Update()
{
	sprite->Update(CTimer::GetInstance().deltaTime);
}

void CGameObject::Render()
{
	sprite->Draw();

	App::Print(10, 70, "GameObject Render", 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameObject::Cleanup()
{
	delete this;
}

void CGameObject::Destroy()
{
}

void CGameObject::OnDestroy()
{
}
