#pragma region Programmer
// GameManager by Frank Sonntag
#pragma endregion

#pragma once

#pragma region project include
#include "EGameLoop.h"
#include "TexturedEntity.h" 
#include "Text.h"
#include "Timer.h"
#include "Sound.h"
#pragma endregion

#pragma region system include
#include <list>
#pragma endregion

class GPlayer;
class CEntity;

class GGameManager

{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GGameManager();
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~GGameManager();
#pragma endregion

#pragma region public function
	/// <summary>
	/// Reset the GameManager
	/// </summary>
	void Reset();

	/// <summary>
	/// adds player to team
	/// </summary>
	/// <param name="_player">player to be added</param>
	/// <param name="_team">index of team</param>
	void AddPlayer(GPlayer* _player, int _team);

	/// <summary>
	/// switch player in a team
	/// </summary>
	/// <param name="_team">index of team</param>
	std::list<GPlayer*> SwitchPlayer(std::list<GPlayer*> _team);

	/// <summary>
	/// update the gameloop
	/// </summary>
	void Update(float _deltaTime);

	/// <summary>
	/// reset variables after one round
	/// </summary>
	void ResetRound();

	/// <summary>
	/// returns true if player is in team 1, false if player is in team 2
	/// </summary>
	bool PlayerinTeam1(GPlayer* _player);

	/// <summary>
	/// removes player from his team list
	/// </summary>
	/// <param name="_player">player to remove</param>
	void RemovePlayer(GPlayer* _player);

	/// <summary>
	/// creates move timer
	/// </summary>
	void CreateMoveTimer();

	/// <summary>
	/// resets move timer
	/// </summary>
	void ResetMoveTimer();

	/// <summary>
	/// checks if a team has won
	/// </summary>
	bool WinCheck();
#pragma endregion

#pragma region public inline function

	/// <summary>
	/// get team 1 list
	/// </summary>
	/// <returns>list of team 1 players</returns>
	inline std::list<GPlayer*> GetTeam1() { return m_pTeam1; }

	/// <summary>
	/// get team 2 list
	/// </summary>
	/// <returns>list of team 2 players</returns>
	inline std::list<GPlayer*> GetTeam2() { return m_pTeam2; }

	/// <summary>
	/// get number of rounds
	/// </summary>
	/// <returns>number of rounds</returns>
	inline int GetRounds() { return m_rounds; }

	/// <summary>
	/// set round
	/// </summary>
	/// <param name="_rounds">number of rounds</param>
	inline void SetRounds(int _rounds) { m_rounds = _rounds; }

	/// <summary>
	/// get number of bullets
	/// </summary>
	/// <returns></returns>
	inline int GetBulletCounter() { return m_bulletCounter; }

	/// <summary>
	/// set number of bullets
	/// </summary>
	/// <param name="_bullets">number of bullets since game start</param>
	inline void SetBulletCounter(int _bullets) { m_bulletCounter = _bullets; }

	/// <summary>
	/// defines if the timer has expired or is still counting down
	/// </summary>
	/// <param name="_timerDown">timer down true = timer has expired, false = timer is still counting down</param>
	inline void SetTimerDown(bool _timerDown) { m_timerDown = _timerDown; }

	/// <summary>
	/// get timer down
	/// </summary>
	/// <returns>timer down true = timer has expired, false = timer is still counting down</returns>
	inline bool GetTimerDown() { return m_timerDown; }

	/// <summary>
	/// sets current player
	/// </summary>
	/// <param name="_player">current player</param>
	inline void SetCurrentPlayer(GPlayer* _player) { m_pCurrentPlayer = _player; }

	/// <summary>
	/// sets selected team
	/// </summary>
	/// <param name="_selectedTeam">selected team</param>
	/// <returns>true = team 1, false = team 2</returns>
	inline void SetSelectedTeam(bool _selectedTeam) { m_selectedTeam = _selectedTeam; }

	/// <summary>
	/// gets selected team
	/// </summary>
	/// <returns>selected team, true = team 1, false = team 2</returns>
	inline bool GetSelectedTeam() {	return m_selectedTeam; }

	/// <summary>
	/// set eStatus
	/// </summary>
	/// <param name="_eStatus">enum for gameloop</param>
	/// <returns>eStatus</returns>
	inline void SetEStatus(EGameLoop _eStatus) { m_eStatus = _eStatus; }

	/// <summary>
	/// get eStatus
	/// </summary>
	/// <returns>eStatus</returns>
	inline EGameLoop GetEStatus() { return m_eStatus; }

	/// <summary>
	/// set is moved
	/// </summary>
	/// <param name="_isMoved">is moved, true = player was moved, false = player wasn't moved</param>
	inline void SetIsMoved(bool _isMoved) { m_isMoved = _isMoved; }

	/// <summary>
	/// get is moved
	/// </summary>
	/// <returns>is moved, true = player was moved, false = player wasn't moved</returns>
	inline bool GetIsMoved() { return m_isMoved; }

	/// <summary>
	/// set is shooted
	/// </summary>
	/// <param name="_isShooted">is shooted, true = bullet shooted, false = no shoot yet</param>
	inline void SetIsShooted(bool _isShooted) { m_isShooted = _isShooted; }

#pragma endregion


private:
#pragma region private variable
	/// <summary>
	/// selected team, true = team 1, false = team 2
	/// </summary>
	bool m_selectedTeam = false;

	/// <summary>
	/// counts bullet, so that only one bullet spawns in shoot phase
	/// </summary>
	int m_bulletCounter = 1;

	/// <summary>
	/// number of rounds as char
	/// </summary>
	char m_charRounds[10];

	/// <summary>
	/// true = player was moved in round, false = player wasn't moved in round
	/// </summary>
	bool m_isMoved = false; 

	/// <summary>
	/// defines if the timer is down or still counting
	/// false = player can move, true = player can not move, has to shoot
	/// </summary>
	bool m_timerDown = false; 

	/// <summary>
	/// defines if the players has shot
	/// true = player has shot, false = player has not shot yet
	/// </summary>
	bool m_isShooted = false;

	/// <summary>
	/// rounds counter
	/// </summary>
	int m_rounds = 1;

	/// <summary>
	/// initial game status is start 
	/// </summary>
	EGameLoop m_eStatus = START;

#pragma endregion

#pragma region private pointer
	/// <summary>
	/// number of rounds as text
	/// </summary>
	CText* m_pRoundsText = nullptr;

	/// <summary>
	/// current player
	/// </summary>
	GPlayer* m_pCurrentPlayer = nullptr;

	/// <summary>
	/// win sound
	/// </summary>
	CSound* m_pWinSound = nullptr;

	/// <summary>
	/// text for moveTimer in world
	/// </summary>
	GTimer* moveTimerText = nullptr;

	/// <summary>
	/// list with all players of team 1
	/// </summary>
	std::list<GPlayer*> m_pTeam1;

	/// <summary>
	/// list with all players of team 2
	/// </summary>
	std::list<GPlayer*> m_pTeam2;
#pragma endregion
};

