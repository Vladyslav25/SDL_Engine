#include "TextureManagement.h"
#include "Texture.h"

CTextureManagement::~CTextureManagement()
{
	// while textures in map
	while (m_pTextures.size() > 0)
	{
		// delete first texture
		delete m_pTextures.begin()->second;

		// erase first element
		m_pTextures.erase(m_pTextures.begin());
	}
}
