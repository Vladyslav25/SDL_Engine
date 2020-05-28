#pragma region project include
#include "Time.h"
#pragma endregion

#pragma region variable
float CTime::m_deltaTime = 0.0f;
int CTime::m_fps = 0;
#pragma endregion

#pragma region public variable
// update time
void CTime::Update()
{
	// time since application start in milliseconds
	clock_t now = clock();

	// difference to last update
	clock_t diff = now - m_lastUpdate;

	// calculate time since last frame
	m_deltaTime = diff / (float)CLOCKS_PER_SEC;

	// set last update time to now
	m_lastUpdate = now;

	// increase frames since last update
	m_framesSinceLastUpdate++;

	// increase time since last update
	m_timeSinceLastTimeStamp += diff;

	// if time since last update higher than clocks per second
	if (m_timeSinceLastTimeStamp > CLOCKS_PER_SEC)
	{
		// set frames per second
		m_fps = m_framesSinceLastUpdate;

		// reset frames since last update
		m_framesSinceLastUpdate = 0;

		// decrease time since last time stamp
		m_timeSinceLastTimeStamp -= CLOCKS_PER_SEC;

		// reset delta time
		m_deltaTime = 0.0f;
	}
}
#pragma endregion