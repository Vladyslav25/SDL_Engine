#pragma once

#pragma region sdl include
#include <SDL_Rect.h>
#pragma endregion

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// rectangle struct
/// </summary>
struct SRect : public SDL_Rect
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	SRect() { x, y, w, h = 0; }

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_size">size of rect (x = width)</param>
	/// <param name="_pos">position of rect</param>
	SRect(SVector2 _size, SVector2 _pos = SVector2())
	{
		x = (int)_pos.X;
		y = (int)_pos.Y;
		w = (int)_size.X;
		h = (int)_size.Y;
	}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_w">width of rect</param>
	/// <param name="_h">height of rect</param>
	/// <param name="_x">x position</param>
	/// <param name="_y">y position</param>
	SRect(int _w, int _h, int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
#pragma endregion

#pragma region public inline void
#pragma region Programmer Vladyslav Sorokin
	/// <summary>
	/// Return the Rect Position
	/// </summary>
	/// <returns>Rect Position as Vector 2d</returns>
	inline SVector2 GetPos()
	{
		return SVector2((float)x,(float)y);
	}

	/// <summary>
	/// Set the Position of the Rect
	/// </summary>
	/// <param name="_x">X Position</param>
	/// <param name="_y">Y Position</param>
	inline void SetPos(float _x, float _y)
	{
		x = (int)_x;
		y = (int)_y;
	}

	/// <summary>
	/// Set the Position of the Rect
	/// </summary>
	/// <param name="_pos">Position as Vector 2d</param>
	inline void SetPos(SVector2 _pos)
	{
		x = (int)_pos.X;
		y = (int)_pos.Y;
	}
#pragma endregion
#pragma endregion
};