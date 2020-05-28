#pragma region Programmer
// gamemanager by Frank Sonntag
#pragma endregion

#include <cstdio>

#pragma region project include
#include "GameManager.h"
#include "Player.h"
#include "MoveEntity.h"
#include "ContentManagement.h"
#include "Renderer.h"
#include "Engine.h"
#include "EGameLoop.h"
#include "Input.h"
#include "Timer.h"
#include "World.h"
#include "Game.h"
#include "Macro.h"
#include "Text.h"
#include "MenuScene.h"
#include "MainScene.h"
#pragma endregion

#pragma region constructor
GGameManager::GGameManager()
{
}
#pragma endregion

#pragma region destructor
GGameManager::~GGameManager()
{
}
#pragma endregion

void GGameManager::Reset() // by Vladi
{
	//reset all var for a new game, after the last gameloop ends
	m_bulletCounter = 1;
	m_pRoundsText = nullptr;
	m_charRounds[10];
	m_pCurrentPlayer = nullptr;
	m_isMoved = false;
	m_timerDown = false;
	m_isShooted = false;
	m_rounds = 1;
	m_eStatus = START;
	moveTimerText = nullptr;
	m_pTeam1.clear();
	m_pTeam2.clear();
	m_selectedTeam = false;
	m_pWinSound = nullptr;
}

// list of Enums Gameloop:
// START,
// TEAMSELECTION,
// PLAYERSELECTION,
// MOVEPHASE,
// SHOOTPHASE,
// WINCHECK,
// RESET

#pragma region Update gameloop
#pragma region Programmer
// update gameloop by Frank Sonntag
#pragma endregion
/// <summary>
/// update the gameloop
/// </summary>
void GGameManager::Update(float _deltaTime)
{
	if (m_eStatus == PLAYERSELECTION || m_eStatus == TEAMSELECTION)
	{
		// switch the controll of the ants in the teams between the rounds

		// if team 1 and team 2 are filled with ants
		if (m_pTeam1.size() > 0 && m_pTeam2.size() > 0)
		{
			// if front ant of team 1 is controlled and not the first update
			if (m_pTeam1.front()->GetControlled() && !m_pTeam1.front()->GetFirstUpdate())
			{
				// set first update for ant in team 1 true
				m_pTeam1.front()->SetFirstUpdate(true);
				// set first update for ant in team 2 false
				m_pTeam2.front()->SetFirstUpdate(false);
			}
			// if front ant of team 2 is controlled and not the first update
			if (m_pTeam2.front()->GetControlled() && !m_pTeam2.front()->GetFirstUpdate())
			{
				// set first update for ant in team 2 true
				m_pTeam2.front()->SetFirstUpdate(true);
				// set first update for ant in team 1 false
				m_pTeam1.front()->SetFirstUpdate(false);
			}
		}

		// removes currents rounds text
		CTM->RemoveEntity(m_pRoundsText);

		// gets new rounds text
		sprintf_s(m_charRounds, "%d", GGM->GetRounds());

		// place round counter text in mainscene
		m_pRoundsText = new CText(m_charRounds, GAME->m_PArial, SRect(36, 27, (int)(0.5f * SCREEN_WIDTH - 19), 95), SColor(255, 0, 0, 255));

		// add round timer text as UI
		CTM->AddUIEntity(m_pRoundsText);
	}


#pragma region switch eStatus in gameloop
	switch (m_eStatus)
	{
	case TEAMSELECTION:
		// switches selected team after a round
		SetSelectedTeam(!GetSelectedTeam());

		//switch to playerselection
		m_eStatus = PLAYERSELECTION;
		break;

	case PLAYERSELECTION:

		// selected team:
		// bool is initialized in .h
		// true = Team 1 / false = Team 2

		// switch player in list of selected team
		if (GetSelectedTeam())
		{
			// activate controll for first ant in team 1
			m_pTeam1.front()->ActivateControll();
		}

		else
		{
			// activate controll for first ant in team 2
			m_pTeam2.front()->ActivateControll();
		}

		// switch to next phase, when player is moved
		if (m_isMoved)
			m_eStatus = MOVEPHASE;

		break;

	case MOVEPHASE:
		// if move timer is down and ant is grounded (no switch in the air!)
		if (m_timerDown && m_pCurrentPlayer->GetGrounded())

			// go to shoot phase
			m_eStatus = SHOOTPHASE;

		break;

	case SHOOTPHASE:
		// if shooted, check if a team has won
		if (m_isShooted)
			m_eStatus = WINCHECK;
		break;


	case WINCHECK:
		// checks if a team has won the game
		// true = minimum one ant in every team is alive
		if (WinCheck())
			// go to reset case for next round
			m_eStatus = RESET;

		else
		{
			// create win sound, if it doesn't exist
			if (m_pWinSound == nullptr)
				m_pWinSound = new CSound("Audio/S_Win.ogg");

			//play win sound
			m_pWinSound->Play();

			// reset variables of the game manager
			Reset();

			// create new main scene and go to menu scene
			ENGINE->ChangeScene(new GMenuScene());
			m_eStatus = START;
		}
		break;

	case RESET:
		// reset variables of gamemanager for next round
		ResetRound();

		// increase round counter 
		m_rounds++;

		// after one loop go to teamselection
		m_eStatus = TEAMSELECTION;
		break;

	default:
		break;
	}

}

#pragma endregion


void GGameManager::ResetRound()
{
	SetIsMoved(false);
	m_timerDown = false; // false = player can move, true = player can not move, has to shoot
	m_isShooted = false;

	// reset move timer
	ResetMoveTimer();

	// if team 1
	if (GetSelectedTeam())
		// deactivate controll of ant in team 1
		m_pTeam1.front()->DeactivateControll();

	// if team 2
	else
		// deactivate controll of ant in team 2
		m_pTeam2.front()->DeactivateControll();
}

bool GGameManager::PlayerinTeam1(GPlayer* _player)
{
	// checks for all players in team 1
	for (GPlayer* pPlayer : m_pTeam1)
	{
		// if player is in team 1 list
		if (_player == pPlayer)
			return true; // team 1
	}
	return false; // team 2
}


void GGameManager::RemovePlayer(GPlayer* _player)
{
	// if player is in team 1
	if (PlayerinTeam1(_player))
	{
		// for all players in team 1
		for (GPlayer* pPlayer : m_pTeam1)
		{
			if (_player == pPlayer)
			{
				// remove player from list team 1
				m_pTeam1.remove(_player);
				CTM->RemoveEntity(_player->GetTopTexture()); // von Vladi angepasst
				CTM->RemoveEntity(_player->GetDownTexture()); // von Vladi angepasst
				CTM->RemoveEntity(_player); // von Vladi angepasst
				return;
			}
		}
	}

	else {
		// for all players in team 2
		for (GPlayer* pPlayer : m_pTeam2)
		{
			if (_player == pPlayer)
			{
				// remove player from list team 2
				m_pTeam2.remove(_player);
				CTM->RemoveEntity(_player->GetTopTexture()); // von Vladi angepasst
				CTM->RemoveEntity(_player->GetDownTexture()); // von Vladi angepasst
				CTM->RemoveEntity(_player); // von Vladi angepasst
				return;
			}
		}
	}


}

void GGameManager::CreateMoveTimer()
{
	// create move timer
	moveTimerText = new GTimer(MOVETIMER, GAME->m_PArial, SRect(40, 30, (int)(0.5f * SCREEN_WIDTH - 19), 40), SColor(0, 0, 0, 255));
	moveTimerText->SetInWorld(false);
	// add move timer as UI
	CTM->AddUIEntity(moveTimerText);
}

void GGameManager::ResetMoveTimer()
{
	// set timer down true
	m_timerDown = false;

	// reset timer for next movephase 
	moveTimerText->SetMoveTimer(MOVETIMER);
}
bool GGameManager::WinCheck()
{
	// counts alive ants
	// bool antsAlive = false;

	// if a team is empty, 
	if (m_pTeam1.size() == 0 || m_pTeam2.size() == 0)
		return false; // one team has no alive ants anymore, the other team has won
	else
		return true; // both teams have still alive ants, no team has won yet
}
#pragma endregion


void GGameManager::AddPlayer(GPlayer* _player, int _team)
{
	if (!_player)
		return;

	// assign player to team 1
	if (_team == 1)
		// at the end of list team 1
		m_pTeam1.push_back(_player);

	// assign player to team 2
	if (_team == 2)
		// at the end of list team 2
		m_pTeam2.push_back(_player);
}

std::list<GPlayer*> GGameManager::SwitchPlayer(std::list<GPlayer*> _team)
{
	// switch the controll of the players to the next ant in the list of a team

	// sets controll of ant in the frant on false
	_team.front()->SetControlled(false);

	// push the front ant at the end of the list
	_team.push_back(_team.front());

	// deactivate the controll of the last ant in the list
	_team.back()->SetControlled(false);

	// set first update on false for the last ant in the list
	_team.back()->SetFirstUpdate(false);

	// pop the front ant of the list
	_team.pop_front();

	// activate the controll of the new front ant in a list
	_team.front()->SetControlled(true);

	// team 1 
	if (GetSelectedTeam())
		m_pTeam1 = _team;

	// team 2
	else
		m_pTeam2 = _team;

	// return selected team
	return _team;
}
