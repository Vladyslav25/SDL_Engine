#pragma once

#pragma region project include
#include "MoveEntity.h" 
#include "Sound.h"
#pragma endregion

/// <summary>
/// bullet class
/// </summary>
class GBullet :	public CMoveEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GBullet(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	GBullet(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}
#pragma endregion

	#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GBullet();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;


	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// timer for shot, when bullet hits nothing
	/// </summary>
	float m_shotTime = 5.0f;

#pragma endregion

#pragma region private pointer
	/// <summary>
	/// explosion sound
	/// </summary>
	CSound* m_pExplosion = nullptr;

	/// <summary>
	/// gravestone texture
	/// </summary>
	CTexturedEntity* m_pGraveStone = nullptr;

#pragma endregion
};