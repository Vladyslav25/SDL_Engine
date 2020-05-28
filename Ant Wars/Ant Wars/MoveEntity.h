#pragma once

#pragma region Programmer
// MoveEntity changed by Frank Sonntag
#pragma endregion

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "TexturedEntity.h" 
#pragma endregion

/// <summary>
/// moveable entity class
/// </summary>
class CMoveEntity : public CTexturedEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	CMoveEntity(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CTexturedEntity(_pos, _size)	{}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width and height of object</param>
	/// <param name="_pFileName">absolute file path name</param>
	CMoveEntity(SVector2 _pos, SVector2 _size, const char* _pFileName) : CTexturedEntity(_pos, _size, _pFileName) {}

#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CMoveEntity();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// activate gravity
	/// </summary>
	inline void ActivateGravity() { m_gravity = true; }

	/// <summary>
	/// deactivate gravity
	/// </summary>
	inline void DeactivateGravity() { m_gravity = false; }

	/// <summary> added by Frank Sonntag
	/// activate controll of entity
	/// </summary>
	inline void ActivateControll() { m_isControlled = true; }

	/// <summary> added by Frank Sonntag
	/// deactivate controll of entity
	/// </summary>
	inline void DeactivateControll() { m_isControlled = false; }

	/// <summary>
	/// get movement speed
	/// </summary>
	/// <returns>movement speed</returns>
	inline float GetSpeed() { return m_speed; }

	/// <summary>
	/// set movement speed
	/// </summary>
	/// <param name="_speed">movement speed to set</param>
	inline void SetSpeed(float _speed) { m_speed = _speed; }

	/// <summary>
	/// get movement values
	/// </summary>
	/// <returns>movement values</returns>
	inline SVector2 GetMovement() { return m_movement; }

	/// <summary>
	/// set movement values
	/// </summary>
	/// <param name="_movement">movement values</param>
	inline void SetMovement(SVector2 _movement) { m_movement = _movement; }

	/// <summary>
	/// set falle time
	/// </summary>
	/// <param name="_fallTime">fall time to set</param>
	inline void SetFallTime(float _fallTime) { m_fallTime = _fallTime; }

	/// <summary>
	/// get controlled player
	/// </summary>
	/// <returns>controlled player</returns>
	inline bool GetControlled() { return m_isControlled; }

	/// <summary>
	/// set controlled player
	/// </summary>
	/// <param name="_isControlled">controlled player to set</param>
	inline void SetControlled(bool _isControlled) { m_isControlled = _isControlled; }

#pragma endregion

#pragma region public function
	/// <summary>
	/// fill collision list with near collidable objects
	/// </summary>
	void SetCollisionList();
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// object moveable
	/// </summary>
	bool m_moveable = false;

	/// <summary>
	/// gravity enabled
	/// </summary>
	bool m_gravity = false;

	/// <summary>
	/// entity is on ground
	/// </summary>
	bool m_isGrounded = false;

	/// <summary>
	/// movement speed
	/// </summary>
	float m_speed = 0.0f;

	/// <summary>
	/// timer until collision list update
	/// </summary>
	float m_colTimer = 0.0f;

	/// <summary> 
	/// added by Frank Sonntag
	/// current controlled entity
	/// </summary>
	bool m_isControlled = false;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// movement values
	/// </summary>
	SVector2 m_movement = SVector2();
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// collision target
	/// </summary>
	CTexturedEntity* m_pColTarget;

	/// <summary>
	/// list with all collision objects in range
	/// </summary>
	std::list<CTexturedEntity*> m_pColEntities;
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// time since fall begin
	/// </summary>
	float m_fallTime = 0.0f;
#pragma endregion

#pragma region private function
	/// <summary>
	/// check collision with collidable objects list
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	/// <param name="_movement">movmenet to move to</param>
	/// <param name="_speed">movement speed</param>
	/// <param name="_useGravity">if gravity movement</param>
	void CheckCollision(float _deltaSeconds, SVector2 _movement, float _speed, bool _useGravity, bool _gravityOnly = true); 
#pragma endregion
};