#pragma once

#pragma region Programmer
// Gamemanager by Frank Sonntag
#pragma endregion

#pragma region forward decleration
struct SDL_Window;
struct SDL_Surface;
class CRenderer;
class CContentManagement;
class CTextureManagement;
class GGameManager;
class CScene;
class CTexture;
class CTime;
class CMouse;
#pragma endregion

#pragma region macro value
#define ENGINE CEngine::Get()
#define RENDERER CEngine::Get()->GetRenderer()
#define CTM CEngine::Get()->GetCTM()
#define TTM CEngine::Get()->GetTTM()
#define GGM CEngine::Get()->GetGGM()
#define SURFACE CEngine::Get()->GetSurface()
#pragma endregion

/// <summary>
/// core engine class
/// </summary>
class CEngine
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CEngine() {}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get engine
	/// </summary>
	/// <returns>engine reference</returns>
	inline static CEngine* Get()
	{
		// create engine if not exists
		static CEngine* pEngine = new CEngine();

		// return engine reference
		return pEngine;
	}

	/// <summary>
	/// stop engine
	/// </summary>
	inline void Stop()
	{
		// set running false
		m_isRunning = false;
	}

	/// <summary>
	/// get renderer
	/// </summary>
	/// <returns>renderer reference</returns>
	inline CRenderer* GetRenderer() { return m_pRenderer; }

	/// <summary>
	/// get content management
	/// </summary>
	/// <returns>content management reference</returns>
	inline CContentManagement* GetCTM() { return m_pCTM; }

	/// <summary>
	/// get texture management
	/// </summary>
	/// <returns>content texture management reference</returns>
	inline CTextureManagement* GetTTM()	{ return m_pTTM; }

	/// <summary>
	/// get game manager
	/// </summary>
	/// <returns>game manager reference</returns>
	inline GGameManager* GetGGM() { return m_pGGM; }

	/// <summary>
	/// get sdl surface
	/// </summary>
	/// <returns>sdl surface from window</returns>
	inline SDL_Surface* GetSurface() { return m_pSurface; }
#pragma endregion

#pragma region public function

	/// <summary>
	/// initialize engine
	/// </summary>
	/// <returns>error code</returns>
	int Init();

	/// <summary>
	/// load images
	/// </summary>
	/// <returns>return code</returns>
	int Load();

	/// <summary>
	/// run engine
	/// </summary>
	void Run();

	/// <summary>
	/// clean engine
	/// </summary>
	void Clean();

	/// <summary>
	/// set mouse visible
	/// </summary>
	/// <param name="_visible">visible</param>
	void SetMouseVisible(bool _visible);
	
	/// <summary>
	/// set position of mouse center 
	/// in percentage from upper left
	/// upper left is 0,0
	/// lower right is 1,1
	/// </summary>
	/// <param name="x">x value</param>
	/// <param name="y">y value</param>
	void SetMouseCenter(float x, float y);

	/// <summary>
	/// set mouse texture
	/// </summary>
	/// <param name="_pTexture">texture to set</param>
	void SetMouseTexture(CTexture* _pTexture);

	/// <summary>
	/// change active scene
	/// </summary>
	/// <param name="_pScene">new scene</param>
	void ChangeScene(CScene* _pScene);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// engine is running
	/// </summary>
	bool m_isRunning = true;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl window reference
	/// </summary>
	SDL_Window* m_pWindow = nullptr;

	/// <summary>
	/// sdl surface reference
	/// </summary>
	SDL_Surface* m_pSurface = nullptr;

	/// <summary>
	/// renderer reference
	/// </summary>
	CRenderer* m_pRenderer = nullptr;

	/// <summary>
	/// current active scene reference
	/// </summary>
	CScene* m_pScene = nullptr;

	/// <summary>
	/// content management reference
	/// </summary>
	CContentManagement* m_pCTM = nullptr;

	/// <summary>
	/// texture management
	/// </summary>
	CTextureManagement* m_pTTM = nullptr;

	/// <summary>
	/// game manager
	/// </summary>
	GGameManager* m_pGGM = nullptr;

	/// <summary>
	/// time class reference
	/// </summary>
	CTime* m_pTime = nullptr;

	/// <summary>
	/// mouse class
	/// </summary>
	CMouse* m_pMouse = nullptr;
#pragma endregion

#pragma region private function
	/// <summary>
	/// update every frame
	/// </summary>
	void Update();

	/// <summary>
	/// render every frame
	/// </summary>
	void Render();
#pragma endregion
};