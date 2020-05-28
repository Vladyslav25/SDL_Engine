#pragma region project include
#include "Engine.h"
#include "Renderer.h"
#include "TextureManagement.h"
#include "TexturedEntity.h"
#include "Texture.h"
#pragma endregion

#pragma region constructor
// constructor
CTexturedEntity::CTexturedEntity(SVector2 _pos, SVector2 _size)
{
	// set position of entity
	m_position = _pos;

	// set rect width and height
	m_rect.w = (int)_size.X;
	m_rect.h = (int)_size.Y;
}

// constructor
CTexturedEntity::CTexturedEntity(SVector2 _pos, SVector2 _size, const char * _pFileName) : CTexturedEntity(_pos, _size)
{
	// if texture not in texture management create texture and add to management
	if (!TTM->GetTexture(_pFileName))
		TTM->AddTexture(_pFileName, new CTexture(_pFileName));

	// set texture
	m_pTexture = TTM->GetTexture(_pFileName);
}

#pragma endregion

CTexturedEntity::~CTexturedEntity()
{
}

#pragma region public override function
// update every frame
void CTexturedEntity::Update(float _deltaTime)
{
	// set position of rect
	m_rect.x = (int)m_position.X;
	m_rect.y = (int)m_position.Y;
}

// render every frame
void CTexturedEntity::Render()
{
	// render texture at rect
	RENDERER->RenderTexture(m_pTexture, &m_rect, &m_srcRect, m_angle, m_mirror, m_inWorld);
}
#pragma endregion