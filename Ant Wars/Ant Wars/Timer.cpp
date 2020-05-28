#pragma region Programmer
// Programmed by Frank Sonntag
#pragma endregion

#pragma region project include
#include "Timer.h"
#include "GameManager.h"
#include "Engine.h"
#include "Macro.h"
#pragma endregion

#pragma region public override function

// destructor
GTimer::~GTimer()
{
}

// update every frame
void GTimer::Update(float _deltaTime)
{
	// only update timer, when in movephase
	if (GGM->GetEStatus() == MOVEPHASE)
	{
		// reduce timer with deltatime
		m_timer -= _deltaTime;

		// cast float into text
		sprintf_s(m_charTimer, "%d", (int)m_timer);
		m_pText = m_charTimer;

		// if countdown is expired
		if (m_timer <= 0)
		{
			// set timer down true
			GGM->SetTimerDown(true);

			// reset timer for next movephase 
			m_timer = MOVETIMER;
		}
	}

	// load text
	Load();
}
#pragma endregion