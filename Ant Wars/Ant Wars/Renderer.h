#pragma once

#pragma region project include
#include "Vector2.h"
#pragma endregion

#pragma region forward decleration
struct SRect;
class CTexture;
struct SDL_Window;
struct SDL_Renderer;
#pragma endregion

/// <summary>
/// renderer class to render textures
/// </summary>
class CRenderer
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pWindow">sdl window reference</param>
	CRenderer(SDL_Window* _pWindow);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CRenderer();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl renderer
	/// </summary>
	/// <returns>sdl renderer reference</returns>
	inline SDL_Renderer* GetSDLRenderer() { return m_pRenderer; }

	/// <summary>
	/// get camera position
	/// </summary>
	/// <returns>camera position</returns>
	inline SVector2 GetCamera() { return m_camera; }

	/// <summary>
	/// set camera position
	/// </summary>
	/// <param name="_pos">position to set</param>
	inline void SetCamera(SVector2 _pos) { m_camera = _pos; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// clear current screen
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture reference</param>
	/// <param name="_pDstRect">destination rect on screen reference</param>
	/// <param name="_pSrcRect">source rect of texture reference</param>
	/// <param name="_angle">angle of texture</param>
	/// <param name="_mirror">x != 0 than mirror horizontal, y != 0 than mirror vertical</param>
	/// <param name="_inWorld">texture is rendered in world or screen (UI)</param>
	void RenderTexture(CTexture* _pTexture, SRect* _pDstRect = nullptr, SRect* _pSrcRect = nullptr, 
		float _angle = 0.0f, SVector2 _mirror = SVector2(), bool _inWorld = true);

	/// <summary>
	/// present rendered screen
	/// </summary>
	void Present();
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// camera position
	/// </summary>
	SVector2 m_camera = SVector2();
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl renderer reference
	/// </summary>
	SDL_Renderer* m_pRenderer = nullptr;
#pragma endregion
};