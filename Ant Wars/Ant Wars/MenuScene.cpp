#pragma region Programmer
// Programmed by Frank Sonntag
#pragma endregion

#pragma region project include
#include "MenuScene.h"
#include "Engine.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Text.h"
#include "MainScene.h"
#include "Input.h"
#include "Texture.h"
#include "Macro.h"
#include "Physic.h"
#pragma endregion

#pragma region Programmer
// menu scene by Frank Sonntag
#pragma endregion

#pragma region public function
// initialize scene
void GMenuScene::Load()
{
	// initialize mouse
	CTexture* pMouse = new CTexture("Texture/Mouse/T_Mouse.png");
	ENGINE->SetMouseTexture(pMouse);
	ENGINE->SetMouseCenter(0.5f, 0.5f);
	ENGINE->SetMouseVisible(true);

	// add background
	m_pBackground = new CTexturedEntity(SVector2(), SVector2(), "Texture/Environment/Background/T_MainMenu.png");
	m_pBackground->SetInWorld(false); 

	// add start button to menu
	m_pStartButton = new CTexturedEntity(SVector2(0.5f * SCREEN_WIDTH - 200.0f, 0.5f * SCREEN_HEIGHT - 100.0F), SVector2(400.0F, 168.0F), "Texture/Buttons/T_Play_Button.png");
	m_pStartButton->SetInWorld(false); 

	// add quit button to menu
	m_pQuitButton = new CTexturedEntity(SVector2(0.5f * SCREEN_WIDTH - 200.0f, 0.5f * SCREEN_HEIGHT + 100.0f), SVector2(400.0F, 168.0F), "Texture/Buttons/T_Quit_Button.png");
	m_pQuitButton->SetInWorld(false); 

	// add background & buttons as UI
	CTM->AddUIEntity(m_pBackground);
	CTM->AddUIEntity(m_pStartButton);
	CTM->AddUIEntity(m_pQuitButton);
}

// clean scene
void GMenuScene::Clean()
{
	// remove background & buttons
	CTM->RemoveEntity(m_pBackground);
	CTM->RemoveEntity(m_pStartButton);
	CTM->RemoveEntity(m_pQuitButton);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{
	// if left mouse button is pressed and position collides with button position
	if (CInput::GetMouseButtonDown(0))
	{
		// check collision between rect of button and mouse position
		if (CPhysic::RectRectCollision(m_pStartButton->GetRect(), SRect(1, 1, (int)(CInput::GetMousePosition().X), (int)(CInput::GetMousePosition().Y))))
		{
			// load main scene
			
			ENGINE->ChangeScene(new GMainScene());
		}
		else if (CPhysic::RectRectCollision(m_pQuitButton->GetRect(), SRect(1, 1, (int)(CInput::GetMousePosition().X), (int)(CInput::GetMousePosition().Y))))
		{
			// quit game
			GAME->QuitGame();
		}
	}
}

// render every frame
void GMenuScene::Render()
{

}
#pragma endregion