#pragma once

#pragma region project include
#include "MoveEntity.h"
#pragma endregion

#pragma region forward decleration
class CAnimation;
class CSound;
#pragma endregion

/// <summary>
/// player class
/// </summary>
class GPlayer : public CMoveEntity
{
public:

#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of object</param>
	/// <param name="_size">width (x) and height (y) of object</param>
	GPlayer(SVector2 _pos = SVector2(), SVector2 _size = SVector2()) : CMoveEntity(_pos, _size) {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of entity</param>	
	/// <param name="_size">size of texture (x = width, y = height)</param>
	/// <param name="_pFileName">relative path name of texture</param>
	GPlayer(SVector2 _pos, SVector2 _size, const char* _pFileName) : CMoveEntity(_pos, _size, _pFileName) {}

#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer();
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

	void UpdateAnimation(float _deltaTime);

#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize player
	/// </summary>
	void Init();

#pragma endregion

#pragma region public inline function

	/// <summary>
	/// get first update
	/// </summary>
	/// <returns>first update</returns>
	inline bool GetFirstUpdate() { return m_pFirstUpdate; }

	/// <summary>
	/// set first update
	/// </summary>
	/// <returns>first update</returns>
	inline void SetFirstUpdate(bool _firstUpdate) { m_pFirstUpdate = _firstUpdate; }

	bool Death();

	/// <summary>
	/// get player health points
	/// </summary>
	/// <returns></returns>
	inline int GetHP() { return m_pHP; }

	/// <summary>
	/// set player health points
	/// </summary>
	/// <param name="_hp"></param>
	inline void SetHP(int _hp) { m_pHP = _hp; }

	/// <summary>
	/// add damage 
	/// </summary>
	/// <param name="_damage">damage points</param>
	inline void AddDamage(int _damage) { m_pHP -= _damage; }

	/// <summary>
	/// get top texture
	/// </summary>
	/// <returns>top texture</returns>
	inline CTexturedEntity* GetTopTexture() { return m_pTextureTop; }

	/// <summary>
	/// get down texture
	/// </summary>
	/// <returns>down texture</returns>
	inline CTexturedEntity* GetDownTexture() { return m_pTextureDown; }

	/// <summary>
	/// get is grounded
	/// </summary>
	/// <returns>is grounded, true = grounded, false = not grounded, in the air</returns>
	inline bool GetGrounded() { return m_isGrounded; }
#pragma endregion

#pragma region public Variabel
#pragma region by Vladyslav Sorokin
	/// <summary>
	/// bool to skip the Wall Check
	/// </summary>
	bool m_skipWallCheck = false;

	/// <summary>
	/// bool to save if the Player has preddes the D Key
	/// </summary>
	bool m_PressingD = false;

	/// <summary>
	/// bool to save if the Player has preddes the A Key
	/// </summary>
	bool m_PressingA = false;

	/// <summary>
	/// Rect Width as float
	/// </summary>
	float RectWidth = (float)m_rect.w;

	/// <summary>
	/// Rect Hight as float
	/// </summary>
	float RectHight = (float)m_rect.h;

#pragma endregion
#pragma endregion

private:

#pragma region private variable

#pragma region by Frank Sonntag
	/// <summary>
	/// first update of player
	/// </summary>
	bool m_pFirstUpdate = false;

	/// <summary>
	/// player health points
	/// </summary>
	int m_pHP = 100;

	/// <summary>
	/// is throwing grenade, used for shoot-animation
	/// </summary>
	bool m_IsThrowingGrenade = false;

	/// <summary>
	/// spawn side, -1 = left, 1 = right
	/// </summary>
	int spawnSide = -1;

	/// <summary>
	/// bullet counter
	/// </summary>
	int bulletCounter = 1;

	/// <summary>
	/// shoot power
	/// </summary>
	float shootpower = 1.0f;

	/// <summary>
	/// sinus
	/// </summary>
	float sinus;

	/// <summary>
	/// cosinus
	/// </summary>
	float cosinus;

	/// <summary>
	/// radius from middle point of player
	/// </summary>
	float radius;

#pragma endregion

#pragma region by Vladi
	/// <summary>
	/// WW Down Rect
	/// </summary>
	SRect DownRect;

	/// <summary>
	/// WW Up Rect
	/// </summary>
	SRect UpRect;

	/// <summary>
	/// WW Left Rect
	/// </summary>
	SRect LeftRect;

	/// <summary>
	/// WW Right Rect
	/// </summary>
	SRect RightRect;

	/// <summary>
	/// bool if the WW Down Rect have Collision
	/// </summary>
	bool DownRectActiv;

	/// <summary>
	/// bool if the WW Up Rect have Collision
	/// </summary>
	bool UpRectActiv;

	/// <summary>
	/// bool if the WW Left Rect have Collision
	/// </summary>
	bool LeftRectActiv;

	/// <summary>
	/// bool if the WW Right Rect have Collision
	/// </summary>
	bool RightRectActiv;

	/// <summary>
	/// Vector saves the Currend Ground
	/// </summary>
	SVector2 currentGround = SVector2(0, 0);

#pragma endregion

#pragma region private pointer

#pragma region by Frank Sonntag
	/// <summary>
	/// current animation pointer
	/// </summary>
	CAnimation* m_pCurrentAnimTop = nullptr;

	/// <summary>
	/// idle animation reference
	/// </summary>
	CAnimation* m_pIdleAnimTop = nullptr;

	/// <summary>
	/// shoot animation reference
	/// </summary>
	CAnimation* m_pShootAnimTop = nullptr;

	/// <summary>
	/// current animation pointer
	/// </summary>
	CAnimation* m_pCurrentAnimDown = nullptr;

	/// <summary>
	/// idle animation reference
	/// </summary>
	CAnimation* m_pIdleAnimDown = nullptr;

	/// <summary>
	/// walk animation reference
	/// </summary>
	CAnimation* m_pWalkAnimDown = nullptr;

	/// <summary>
	/// shot sound
	/// </summary>
	CSound* m_pShotSound = nullptr;

	/// <summary>
	/// jump sound
	/// </summary>
	CSound* m_pJump = nullptr;

	/// <summary>
	/// walking sound
	/// </summary>
	CSound* m_pWalking = nullptr;

	/// <summary>
	/// attack sound
	/// </summary>
	CSound* m_pAttack = nullptr;

	/// <summary>
	/// explosion sound
	/// </summary>
	CSound* m_pExplosion = nullptr;

	/// <summary>
	/// death sound
	/// </summary>
	CSound* m_pDeathSound = nullptr;

	/// <summary>
	/// top texture
	/// </summary>
	CTexturedEntity* m_pTextureTop = nullptr;

	/// <summary>
	/// down texture
	/// </summary>
	CTexturedEntity* m_pTextureDown = nullptr;

#pragma endregion


#pragma region private functions by Vladi
	/// <summary>
	/// Create the WW Rects
	/// </summary>
	void SetWallRects();

	/// <summary>
	/// Update the Position of the WW Rects
	/// </summary>
	void SetWallRectsPos();

	/// <summary>
	/// Check if the WW REcts have Collision
	/// </summary>
	void CheckForNewGround();
#pragma endregion

#pragma endregion
};