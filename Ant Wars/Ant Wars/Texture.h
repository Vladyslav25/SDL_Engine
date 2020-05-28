#pragma once

#pragma region forward decleration
struct SDL_Texture;
#pragma endregion

/// <summary>
/// texture class
/// </summary>
class CTexture
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">relative path name of texture</param>
	CTexture(const char* _pFileName);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CTexture();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl texture
	/// </summary>
	/// <returns>sdl texture reference</returns>
	inline SDL_Texture* GetSDLTexture() { return m_pTexture; }

	/// <summary>
	/// set sdl texture
	/// </summary>
	/// <param name="_pTexture">sdl texture to set</param>
	inline void SetSDLTexture(SDL_Texture* _pTexture) { m_pTexture = _pTexture; }
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// sdl texture reference
	/// </summary>
	SDL_Texture* m_pTexture = nullptr;
#pragma endregion
};