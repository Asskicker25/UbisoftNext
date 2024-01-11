#include "CGameState.h"
#include "CGameManager.h"

void CGameState::ChangeState(EGameState state)
{
	pGameManager->ChangeState(state);

}

void CGameState::SetGameManager(CGameManager* gameManger)
{
	pGameManager = gameManger;
}
