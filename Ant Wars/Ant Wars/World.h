#pragma once

#pragma region system include
#include <string>  
#pragma endregion

#pragma region project include
#include "TexturedEntity.h" 
#include "Text.h"
#include "Timer.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// world class
/// </summary>
class GWorld : public CTexturedEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pRenderer">renderer</param>
	/// <param name="_pFileName">absolute file path name</param>
	GWorld(const char* _pFileName)
		: CTexturedEntity(SVector2(), SVector2(), _pFileName) {}

	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GWorld();
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize world
	/// </summary>
	void Init();

	/// <summary>
	/// get move timer text
	/// </summary>
	/// <returns>move timer text</returns>
	inline GTimer* GetMoveTimerText() { return moveTimerText; }

#pragma endregion

private:
#pragma region private function
	/// <summary>
	/// load world as string from bmp file
	/// </summary>
	/// <param name="_pFile">file to load from</param>
	/// <returns>world as string</returns>
	string LoadWorldFromBmp(const char* _pFile);
#pragma endregion


#pragma region private pointer
	/// <summary>
	/// text for moveTimer in world
	/// </summary>
	GTimer* moveTimerText = nullptr;

	/// <summary>
	/// world background
	/// </summary>
	CTexturedEntity* m_pWorldBackground = nullptr;

	/// <summary>
	/// timer texture
	/// </summary>
	CTexturedEntity* m_pTimerTexture = nullptr;

#pragma endregion
};