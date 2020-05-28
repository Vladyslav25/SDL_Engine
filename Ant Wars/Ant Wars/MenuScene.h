#pragma once

#pragma region Programmer
// menu scene by Frank Sonntag
#pragma endregion


#pragma region project include
#include "Scene.h" 
#include "TexturedEntity.h"
#pragma endregion

#pragma region forward decleration
class CText;
#pragma endregion

/// <summary>
/// menu game scene
/// </summary>
class GMenuScene : public CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GMenuScene() : CScene() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GMenuScene() { Clean(); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// load scene
	/// </summary>
	virtual void Load() override;

	/// <summary>
	/// clean scene
	/// </summary>
	virtual void Clean() override;

	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// menu background
	/// </summary>
	CTexturedEntity* m_pBackground = nullptr;

	/// <summary>
	/// start button
	/// </summary>
	CTexturedEntity* m_pStartButton = nullptr;

	/// <summary>
	/// quit button
	/// </summary>
	CTexturedEntity* m_pQuitButton = nullptr;

#pragma endregion
};