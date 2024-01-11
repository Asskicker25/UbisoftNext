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


CGameManager* pGameManager;

void Init()
{
	pGameManager = new CGameManager();

	pGameManager->AddState(MAIN_MENU, new CMainMenuGameState());
	pGameManager->AddState(GAMEPLAY, new CGameplayGameState());

	pGameManager->ChangeState(MAIN_MENU);

	pGameManager->Start();
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
}