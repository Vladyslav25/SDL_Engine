#pragma region sdl include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Renderer.h"
#include "Texture.h"
#include "Rect.h"
#include "Config.h"
#include "Macro.h"
#pragma endregion

#pragma region constructor
// constructor
CRenderer::CRenderer(SDL_Window * _pWindow)
{
	// create renderer
	m_pRenderer = SDL_CreateRenderer(
		_pWindow,						// window reference
		-1,								// index
		SDL_RENDERER_ACCELERATED |		// flags (F12)
		SDL_RENDERER_PRESENTVSYNC
	);
}
#pragma endregion

#pragma region destructor
// destructor
CRenderer::~CRenderer()
{
	// if renderer valid destroy renderer
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
}
#pragma endregion

#pragma region public function
// clear current screen
void CRenderer::ClearScreen()
{
	SDL_RenderClear(m_pRenderer);
}

// render texture
void CRenderer::RenderTexture(CTexture* _pTexture, SRect* _pDstRect, SRect* _pSrcRect,
	float _angle, SVector2 _mirror, bool _inWorld)
{
	// if texture not valid return
	if (!_pTexture)
	{
		return;
	}


	// if textre rendered in world and of out camera range
	else if (_inWorld && _pDstRect && (
		(_pDstRect->x < m_camera.X - SCREEN_WIDTH * 0.5f - _pDstRect->w) ||
		(_pDstRect->x > m_camera.X + SCREEN_WIDTH * 0.5f) ||
		(_pDstRect->y < m_camera.Y - SCREEN_HEIGHT * 0.5f - _pDstRect->h) ||
		(_pDstRect->y > m_camera.Y + SCREEN_HEIGHT * 0.5f)
		))
	{
		return;
	}

	// if textre not rendered in world and of out screen return
	else if (!_inWorld && _pDstRect && (
		(_pDstRect->x < -_pDstRect->w) || (_pDstRect->x > SCREEN_WIDTH) ||
		(_pDstRect->y < -_pDstRect->h) || (_pDstRect->y > SCREEN_HEIGHT)
		))
	{
		return;
	}

	// rotation point
	SDL_Point rotationPoint;

	// if destination rect valid
	if (_pDstRect)
	{
		// set rotation point to center
		rotationPoint.x = (int)(_pDstRect->w * 0.5f);
		rotationPoint.y = (int)(_pDstRect->h * 0.5f);

		// if object is rendered in world
		if (_inWorld)
		{
			// add camera offset to destination rect
			_pDstRect->x -= (int)(m_camera.X - SCREEN_WIDTH * 0.5f);
			_pDstRect->y -= (int)(m_camera.Y - SCREEN_HEIGHT * 0.5f);
		}
	}

	// if width or height of destination rect 0 set to nullptr
	if (_pDstRect && (!_pDstRect->h || !_pDstRect->w))
		_pDstRect = nullptr;

	// if width or height of source rect 0 set to nullptr
	if (_pSrcRect && (!_pSrcRect->h || !_pSrcRect->w))
		_pSrcRect = nullptr;

	// flip
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

	// if mirror x not 0 and y 0 set flip to horizontal
	if (_mirror.X && !_mirror.Y)
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

	// if mirror y not 0 and x 0 set flip to vertical
	else if (_mirror.Y && !_mirror.X)
		flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

	// if mirror x and mirror y not 0 add 180 angle
	// mirror horizontal and vertical is the same as 180 angle
	else if (_mirror.X && _mirror.Y)
		_angle += 180.0f;

	// render texture
	SDL_RenderCopyEx(
		m_pRenderer,				// sdl renderer reference
		_pTexture->GetSDLTexture(),	// sdl texture reference
		_pSrcRect,					// source rect of texture
		_pDstRect,					// destination rect to render to on screen
		_angle,						// angle of texture
		&rotationPoint,				// rotation point of angle
		flip						// mirror
	);
}

// present rendered screen
void CRenderer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}
#pragma endregion