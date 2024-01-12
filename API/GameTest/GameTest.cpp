//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
//------------------------------------------------------------------------

#include "src/GameManager/CGameManager.h"
#include "src/GameManager/GameStates/CMainMenuGameState.h"
#include "src/GameManager/GameStates/CGameplayGameState.h"
#include "src/GameManager/GameStates/CLevelCompleteGameState.h"
#include "src/LevelManager/CLevelManager.h"


CGameManager* pGameManager;

void Init()
{
	pGameManager = new CGameManager();

	pGameManager->AddState(MAIN_MENU, new CMainMenuGameState());
	pGameManager->AddState(GAMEPLAY, new CGameplayGameState());
	pGameManager->AddState(LEVEL_COMPLETE, new CLevelCompleteGameState());

	pGameManager->ChangeState(MAIN_MENU);

	pGameManager->Start();
	CLevelManager::GetInstance().Start();
}


void Update(float deltaTime)
{
	pGameManager->Update();
}


void Render()
{	
	pGameManager->Render();
}

void Shutdown()
{	
	pGameManager->Cleanup();
	CLevelManager::GetInstance().Cleanup();

}