#pragma once

#pragma region project include
#include "Entity.h"
#include "Rect.h"
#include "Enum.h"
#pragma endregion

#pragma region forward decleration
class CRenderer;
class CTexture;
#pragma endregion

/// <summary>
/// entity class that can be rendered
/// </summary>
class CTexturedEntity : public CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of entity</param>
	/// <param name="_size">size of texture (x = width, y = height)</param>
	CTexturedEntity(SVector2 _pos = SVector2(), SVector2 _size = SVector2());

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pos">position of entity</param>
	/// <param name="_size">size of texture (x = width, y = height)</param>
	/// <param name="_pFileName">relative path name of texture</param>
	CTexturedEntity(SVector2 _pos, SVector2 _size, const char* _pFileName);

#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CTexturedEntity();
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
	/// <param name="_pRenderer">renderer</param>
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get angle
	/// </summary>
	/// <returns>angle</returns>
	inline float GetAngle() { return m_angle; }

	/// <summary>
	/// set angle
	/// </summary>
	/// <param name="_angle">angle to set</param>
	inline void SetAngle(float _angle) { m_angle = _angle; }

	/// <summary>
	/// set to be rendered in world or screen (UI)
	/// </summary>
	/// <param name="_inWorld">rendered in world</param>
	inline void SetInWorld(bool _inWorld) { m_inWorld = _inWorld; }

	/// <summary>
	/// get collision type
	/// </summary>
	/// <returns>collision type</returns>
	inline ECollisionType GetColType() { return m_colType; }

	/// <summary>
	/// set collision type
	/// </summary>
	/// <param name="_colType">collision type to set</param>
	inline void SetColType(ECollisionType _colType) { m_colType = _colType; }

	/// <summary>
	/// get rect of texture
	/// </summary>
	/// <returns>rect of texture</returns>
	inline SRect GetRect() { return m_rect; }

	/// <summary>
	/// set rect of texture
	/// </summary>
	/// <param name="_rect">rect to set</param>
	inline void SetRect(SRect _rect) { m_rect = _rect; }

	/// <summary>
	/// get source rect of texture
	/// </summary>
	/// <returns>source rect of texture</returns>
	inline SRect GetSrcRect() { return m_srcRect; }

	/// <summary>
	/// set source rect of texture
	/// </summary>
	/// <param name="_rect">source rect to set</param>
	inline void SetSrcRect(SRect _rect) { m_srcRect = _rect; }

	/// <summary>
	/// get mirror
	/// </summary>
	/// <returns>mirror</returns>
	inline SVector2 GetMirror() { return m_mirror; }

	/// <summary>
	/// set mirror
	/// </summary>
	/// <param name="_mirror">mirror to set</param>
	inline void SetMirror(SVector2 _mirror) { m_mirror = _mirror; }
	
	/// <summary>
	/// set texture
	/// </summary>
	/// <param name="_ptexture">texture to set</param>
	inline void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }

#pragma region by Vladi

	/// <summary>
	/// get texture
	/// </summary>
	/// <returns>retunr the pointer of the texture</returns>
	inline CTexture* GetTexture() { return m_pTexture; }
#pragma endregion
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// render angle
	/// </summary>
	float m_angle = 0.0f;

	/// <summary>
	/// texture should be rendered in world or screen (UI)
	/// </summary>
	bool m_inWorld = true;

	/// <summary>
	/// collision type of entity
	/// </summary>
	ECollisionType m_colType = ECollisionType::NONE;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// rect of texture
	/// </summary>
	SRect m_rect = SRect();

	/// <summary>
	/// source rect of texture
	/// </summary>
	SRect m_srcRect = SRect();

	/// <summary>
	/// mirror horizontal and vertical
	/// x != 0 -> mirror horizontal
	/// y != 0 -> mirror vertical
	/// if x != 0 ignore y value
	/// </summary>
	SVector2 m_mirror = SVector2();
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// texture reference
	/// </summary>
	CTexture* m_pTexture = nullptr;
	
#pragma endregion
};