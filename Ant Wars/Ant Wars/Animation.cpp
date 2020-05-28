#pragma region project include
#include "Animation.h"  
#pragma endregion

#pragma region public function
// update every frame
void CAnimation::Update(float _deltaTime)
{
	// increase time
	m_time += _deltaTime;

	// if time higher than animation time / count
	if (m_time > m_animationTime / m_count)
	{
		// increase current frame number
		m_current++;

		// if current is higher than count reset
		if (m_current > m_count)
			m_current = 1;

		// reset time
		m_time = 0.0f;
	}
}

// get current position in texture
SVector2 CAnimation::GetCurrentTexturePosition()
{
	// return vector 2
	SVector2 v;

	// set x of vector 2 by start position x plus width of frame * current
	v.X = m_startPos.X + m_size.X * (m_current - 1);

	// set y of vector2 by start position y
	v.Y = m_startPos.Y;

	// return position of current frame in texture
	return v;
}
#pragma endregion