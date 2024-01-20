#include "CMegaMagnify.h"
#include "../../CPlayerManager.h"

CMegaMagnify::CMegaMagnify()
{
}

void CMegaMagnify::Activate()
{
	CPlayer* player = CPlayerManager::GetInstance().GetOtherPlayer();
	player->pSprite->SetScale(mMagnifyScale);

	Vector2 pos = player->GetPosition();

	//pos.x += player->pSprite->GetWidth() * 0.5f;
	pos.y += player->pSprite->GetHeight();

	player->SetPosition(pos.x, pos.y);

	Vector2 offset = player->pPhysicsShape->pShape->GetOffset();

	offset.y -= player->pSprite->GetHeight() * 0.5f;

	player->pPhysicsShape->pShape->SetOffset(offset.x, offset.y);

}

void CMegaMagnify::Deactivate()
{
	CPlayer* player = CPlayerManager::GetInstance().GetCurrentPlayer();
	player->pSprite->SetScale(1);

	Vector2 pos = player->GetPosition();

	//pos.x += player->pSprite->GetWidth() * 0.5f;
	pos.y -= player->pSprite->GetHeight();

	player->SetPosition(pos.x, pos.y);

	Vector2 offset = player->pPhysicsShape->pShape->GetOffset();

	offset.y += player->pSprite->GetHeight() * 0.5f;

	player->pPhysicsShape->pShape->SetOffset(offset.x, offset.y);
}
