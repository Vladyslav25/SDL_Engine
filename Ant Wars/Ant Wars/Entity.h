#pragma once

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// base entity class
/// </summary>
class CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CEntity() {}
	/// <summary>
	/// destructor by Vladi
	/// </summary>
	virtual ~CEntity();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get tag of entity
	/// </summary>
	/// <returns>tag of entity</returns>
	inline const char* GetTag() { return m_pTag; }

	/// <summary>
	/// set tag of entity
	/// </summary>
	/// <param name="_pTag">tag to set</param>
	inline void SetTag(const char* _pTag) { m_pTag = _pTag; }

	/// <summary>
	/// get position of entity
	/// </summary>
	/// <returns>position of entity</returns>
	inline SVector2 GetPosition() { return m_position; }

	/// <summary>
	/// set position of entity
	/// </summary>
	/// <param name="_pos">position to set</param>
	inline void SetPosition(SVector2 _pos) { m_position = _pos; }

	/// <summary>
	/// add vector2 to position of entity
	/// </summary>
	/// <param name="_vec">vector2 to add</param>
	inline void AddPosition(SVector2 _vec) { m_position = m_position + _vec; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) = 0;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() = 0;
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// tag of entity
	/// </summary>
	const char* m_pTag = nullptr;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// position of entity
	/// </summary>
	SVector2 m_position = SVector2();
#pragma endregion
};