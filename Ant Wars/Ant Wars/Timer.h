#pragma once
#pragma region project include
#include "Text.h"
#pragma endregion

#pragma region system include
#include <cstdio>
#pragma endregion

class GTimer :	public CText
{
public:
	GTimer(float _timer, CFont* _pFont, SRect _rect = SRect(), SColor _color = SColor()) 
		: CText("", _pFont, _rect, _color) { m_timer = _timer; }


#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GTimer();
#pragma endregion

	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	void Update(float _deltaTime) override;

#pragma region public inline function
	/// <summary>
	/// get move timer
	/// </summary>
	/// <returns>move timer</returns>
	inline float GetMoveTimer() { return m_timer; }

	/// <summary>
	/// set move timer
	/// </summary>
	/// <param name="_pText">move timer to set</param>
	inline void SetMoveTimer(float _timer)
	{
		m_timer = _timer;
	}

#pragma region private variable
private:

	/// <summary>
	/// timer 
	/// </summary>
	float m_timer = 15;

	/// <summary>
	/// timer as char
	/// </summary>
	char m_charTimer[10];

#pragma endregion
};

