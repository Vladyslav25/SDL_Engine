#pragma region project include
#include "MainScene.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "World.h"
#include "Music.h"
#include "GameManager.h"
#pragma endregion

#pragma region public function
// load scene
void GMainScene::Load()
{
	// initialize mouse
	ENGINE->SetMouseVisible(false);

	// create world
	m_pWorld = new GWorld("Texture/Environment/World/T_WorldSide.png");
	m_pWorld->Init();
	GGM->SetEStatus(TEAMSELECTION);

	// create music and start playing
	m_pMusic = new CMusic("Audio/M_Background.ogg");
	m_pMusic->Play(true);
}

// clean scene
void GMainScene::Clean()
{
	// delete music
	delete m_pMusic;

	// delete world
	delete m_pWorld;

	// delete all persistant objects
	CTM->CleanPersistantObjects();
}

// update every frame
void GMainScene::Update(float _deltaTime)
{
	
}

// render every frame
void GMainScene::Render()
{

}
#pragma endregion