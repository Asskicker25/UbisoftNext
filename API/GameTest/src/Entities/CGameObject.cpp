#include "CGameObject.h"


CGameObject::CGameObject()
{
}

void CGameObject::Start()
{
}

void CGameObject::Update()
{
}

void CGameObject::Render()
{
	App::Print(10, 70, "GameObject Render", 1.0f, 0.0f, 1.0f, GLUT_BITMAP_HELVETICA_10);
}

void CGameObject::Cleanup()
{
}

void CGameObject::Destroy()
{
}

void CGameObject::OnDestroy()
{
}
