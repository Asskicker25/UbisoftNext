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

	pos.x += player->pSprite->GetWidth() * 0.5f;
	pos.y += player->pSprite->GetHeight() * 0.5f;

	player->SetPosition(pos.x, pos.y);

}

void CMegaMagnify::Deactivate()
{
}
