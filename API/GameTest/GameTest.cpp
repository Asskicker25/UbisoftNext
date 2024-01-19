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
#include "src/Timer/CTimer.h"
#include "src/TimerEvents/CTimerEventsHandler.h"
#include "src/EntityManager/CEntityManager.h"


CGameManager* pGameManager;

void Init()
{
	pGameManager = new CGameManager();

	pGameManager->AddState(MAIN_MENU, new CMainMenuGameState());
	pGameManager->AddState(GAMEPLAY, new CGameplayGameState());
	pGameManager->AddState(LEVEL_COMPLETE, new CLevelCompleteGameState());

	pGameManager->ChangeState(MAIN_MENU);

	pGameManager->Start();
	CTimerEventsHandler::GetInstance().Start();
}


void Update(float deltaTime)
{
	CTimer::GetInstance().mDeltaTime = deltaTime;
	pGameManager->Update();
	CTimerEventsHandler::GetInstance().Update();
}


void Render()
{	
	pGameManager->Render();
}

void Shutdown()
{	
	CTimerEventsHandler::GetInstance().Cleanup();
	pGameManager->Cleanup();
	CLevelManager::GetInstance().Cleanup();
	CEntityManager::GetInstance().Cleanup();
}