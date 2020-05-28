#pragma region Programmer
// Programmed by Frank Sonntag
#pragma endregion

#pragma region system include
#include <string>
#include <SDL_image.h>
#include <cstdio>
#pragma endregion

#pragma region project include
#include "World.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Config.h"
#include "GameManager.h"
#include "Texture.h"
#include "Player.h"
#include "MoveEnemy.h"
#include "Helper.h"
#include "Game.h"
#include "Macro.h"
#include "Timer.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region public function

//destuctor
GWorld::~GWorld()
{
}

// initlialize world
void GWorld::Init()
{
	// add normal forest background
	m_pWorldBackground = new CTexturedEntity(SVector2(0.0f, 0.0f), SVector2(7680.0f, 2544.0f), "Texture/Environment/Background/T_Normal.png");
	m_pWorldBackground->SetInWorld(true);
	CTM->AddSceneEntity(m_pWorldBackground);

	// create world texture
	m_pTexture = new CTexture("Texture/Environment/World/T_World.png");

	// string that defines world
	string world;

	// load world from txt file - deactivated
	//world = LoadStringFromFile("Save/World_AntWars.txt");

	// load world from bmp file
	world = LoadWorldFromBmp("Save/World_AntWars.png");

	// width and height of world
	int width = 0, height = 0;

	// add timer texture
	m_pTimerTexture = new CTexturedEntity(SVector2(0.5f * SCREEN_WIDTH - 64.0f, 0), SVector2(128.0f, 128.0f), "Texture/UI/T_Timer.png");
	m_pTimerTexture->SetInWorld(false);
	CTM->AddSceneEntity(m_pTimerTexture);

	// create move Timer
	GGM->CreateMoveTimer();

#pragma region load txt -deactivateed-

	//// check every char of world through string
	//for (int i = 0; i < world.length(); i++)
	//{
	//	// create textured entity
	//	CTexturedEntity* pEntity = new CTexturedEntity(
	//		SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockWidth),	// position of block
	//		SVector2(GConfig::s_BlockWidth, GConfig::s_BlockWidth)						// size of block
	//	);

	//	// set texture of block
	//	pEntity->SetTexture(m_pTexture);

	//	// x position of texture in atlas texture
	//	int xPosOfTexture = 0;

	//	// switch char in world string
	//	switch (world[i])
	//	{
	//		// if dirt set position of second texture in atlas map
	//	case 'X':
	//		xPosOfTexture = GConfig::s_BlockAtlasWidth;
	//		pEntity->SetColType(ECollisionType::WALL);
	//		break;

	//		// if way set position of third texture in atlas map
	//	case 'W':
	//		xPosOfTexture = 2 * GConfig::s_BlockAtlasWidth;
	//		pEntity->SetColType(ECollisionType::WALL);
	//		break;

	//		// if fire set position of fourth texture in atlas map
	//	case 'L':
	//		xPosOfTexture = 3 * GConfig::s_BlockAtlasWidth;
	//		pEntity->SetColType(ECollisionType::MOVE);
	//		break;

	//		// if player start position spawn player
	//	case 'S':
	//	{
	//		// create player
	//		GPlayer* pAnt1 = new GPlayer
	//		(SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockHeight - 300),
	//			SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight));

	//	// add player to GGM 
	//		GGM->AddPlayer(pAnt1, 1);

	//		// initialize player
	//		pAnt1->Init();
	//		pAnt1->SetSpeed(GConfig::s_BlockWidth * 3.0f);
	//		pAnt1->SetColType(MOVE);
	//		pAnt1->ActivateGravity();
	//		pAnt1->SetCollisionList();
	//		pAnt1->SetHP(PLAYERMAXHP);
	//		pAnt1->SetTag("Ant1");

	//		if (!playerActivated)
	//		{
	//			pAnt1->m_pFirstUpdate = true;
	//			playerActivated = true;
	//			// initial player has activated controll
	//			pAnt1->ActivateControll();
	//		}

	//		// add player to ctm
	//		CTM->AddPersistantEntity(pAnt1);
	//		std::cout << "Type: " << pAnt1->GetColType() << "\n";
	//		// increase width
	//		width++;

	//		// if new line increase height and reset width
	//		if (world[i] == '\n')
	//		{
	//			// increase height and reset width
	//			height++;
	//			width = 0;
	//		}
	//		delete pEntity;

	//		continue;
	//	}

	//	// if enemy spwawn enemy
	//	case 'E':
	//	{
	//		// create enemy
	//		GPlayer* pAnt2 = new GPlayer(
	//			SVector2(width * GConfig::s_BlockWidth, height * GConfig::s_BlockHeight - 300),
	//			SVector2(GConfig::s_PlayerSrcRectWidth, GConfig::s_PlayerSrcRectHeight));

	//		// add player to GGM 
	//		GGM->AddPlayer(pAnt2, 2);

	//		// initialize enemy
	//		pAnt2->Init();
	//		pAnt2->SetSpeed(GConfig::s_BlockWidth * 3.0f);
	//		pAnt2->SetColType(MOVE);
	//		pAnt2->SetCollisionList();
	//		pAnt2->ActivateGravity();
	//		pAnt2->SetHP(PLAYERMAXHP);
	//		pAnt2->SetTag("Ant2");

	//		// add enemy to ctm
	//		CTM->AddPersistantEntity(pAnt2);

	//		// increase width
	//		width++;

	//		// if new line increase height and reset width
	//		if (world[i] == '\n')
	//		{
	//			// increase height and reset width
	//			height++;
	//			width = 0;
	//		}
	//		delete pEntity;
	//		continue;
	//	}

	//	// default
	//	default:
	//		// increase width
	//		width++;

	//		// if new line increase height and reset width
	//		if (world[i] == '\n')
	//		{
	//			// increase height and reset width
	//			height++;
	//			width = 0;
	//		}
	//		delete pEntity;
	//		continue;
	//	}

	//	// set source rect of current block
	//	pEntity->SetSrcRect(SRect(GConfig::s_BlockAtlasWidth, GConfig::s_BlockAtlasHeight, xPosOfTexture, 0));

	//	// add entity to ctm
	//	CTM->AddSceneEntity(pEntity);

	//	// increase width
	//	width++;

	//	// if new line increase height and reset width
	//	if (world[i] == '\n')
	//	{
	//		// increase height and reset width
	//		height++;
	//		width = 0;
	//	}

	//}
#pragma endregion - deactivated

}
#pragma endregion

#pragma region private function
// load world as string from bmp file
string GWorld::LoadWorldFromBmp(const char* _pFile)
{
	// bool to activate controll only for first player in world
	bool playerActivated = false;

	// string to return
	string text = "";

	// create sdl surface from file
	SDL_Surface* pWorld = IMG_Load(GetAssetPath(_pFile, 4).c_str());

	// load pixels in char*
	char* pPixels = (char*)pWorld->pixels;

	// width and height of world
	int width = 0, height = 0;

	// check all pixels
	for (int i = 0; i < pWorld->w * pWorld->h; i++)
	{
		// create textured entity
		CTexturedEntity* pEntity = new CTexturedEntity(
			SVector2((float)(width * GConfig::s_BlockWidth), (float)(height * GConfig::s_BlockWidth)),	// position of block
			SVector2((float)GConfig::s_BlockWidth, (float)GConfig::s_BlockWidth)						// size of block
		);

		// set texture of block
		pEntity->SetTexture(m_pTexture);

		// x position of texture in atlas texture
		int xPosOfTexture = 0;

		// get pixel colors
		uint8_t r = pPixels[0];
		uint8_t g = pPixels[1];
		uint8_t b = pPixels[2];

		// if pixel is 114/57/172
		if (r == 114 && g == 57 && b == 172)
		{
			//text.append("1");
			xPosOfTexture = 0 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::NONE);
		}

		// if pixel is 127/0/255
		else if (r == 127 && g == 0 && b == 255)
		{
			xPosOfTexture = 1 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::NONE);
		}
		// if pixel is 230/230/230
		else if (r == 230 && g == 230 && b == 230)
		{
			xPosOfTexture = 2 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 255/255/255
		else if (r == 255 && g == 255 && b == 255)
		{
			xPosOfTexture = 3 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 57/172/47
		else if (r == 57 && g == 172 && b == 57)
		{
			xPosOfTexture = 4 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 57/57/172
		else if (r == 57 && g == 57 && b == 172)
		{
			xPosOfTexture = 5 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 57/172/172
		else if (r == 57 && g == 172 && b == 172)
		{
			xPosOfTexture = 6 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 29/86&29
		else if (r == 29 && g == 86 && b == 29)
		{
			xPosOfTexture = 7 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 29/29/86
		else if (r == 29 && g == 29 && b == 86)
		{
			xPosOfTexture = 8 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 86/29/86
		else if (r == 86 && g == 29 && b == 86)
		{
			xPosOfTexture = 9 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 172/57/172
		else if (r == 172 && g == 57 && b == 172)
		{
			xPosOfTexture = 10 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 172/57/114
		else if (r == 172 && g == 57 && b == 114)
		{
			xPosOfTexture = 11 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 0/255/0
		else if (r == 0 && g == 255 && b == 0)
		{
			xPosOfTexture = 12 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 0/127/0
		else if (r == 0 && g == 127 && b == 0)
		{
			xPosOfTexture = 13 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 0/255/255
		else if (r == 0 && g == 255 && b == 255)
		{
			xPosOfTexture = 14 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 0/0/255
		else if (r == 0 && g == 0 && b == 255)
		{
			xPosOfTexture = 15 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 0/0/127
		else if (r == 0 && g == 0 && b == 127)
		{
			xPosOfTexture = 16 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 255/0/255
		else if (r == 255 && g == 0 && b == 255)
		{
			xPosOfTexture = 17 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 127/0/127
		else if (r == 127 && g == 0 && b == 127)
		{
			xPosOfTexture = 18 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}
		// if pixel is 255/0/127
		else if (r == 255 && g == 0 && b == 127)
		{
			xPosOfTexture = 19 * GConfig::s_BlockAtlasWidth;
			pEntity->SetColType(ECollisionType::WALL);
		}

		// if pixel is 111/111/111
		else if (r == 111 && g == 111 && b == 111)
		{
			// create player for team 1
			GPlayer* pAnt1 = new GPlayer
			(SVector2((float)(width * GConfig::s_BlockWidth), (float)(height * GConfig::s_BlockWidth)),
				SVector2((float)GConfig::s_PlayerSrcRectWidth, (float)GConfig::s_PlayerSrcRectHeight));

			// add player to GGM 
			GGM->AddPlayer(pAnt1, 1);

			// initialize player
			pAnt1->Init();
			// set speed
			pAnt1->SetSpeed(GConfig::s_BlockWidth * 5.0f);
			// set collision type to move
			pAnt1->SetColType(MOVE);
			// activate gravity
			pAnt1->ActivateGravity();
			// set the Collision-List
			pAnt1->SetCollisionList();
			// set HP to MaxHP
			pAnt1->SetHP(PLAYERMAXHP);
			// tag as Ant 1
			pAnt1->SetTag("Ant1");

			if (!playerActivated)
			{
				pAnt1->SetFirstUpdate(true);
				playerActivated = true;
				// initial player has activated controll
				pAnt1->ActivateControll();
			}

			// add player to ctm
			CTM->AddPersistantEntity(pAnt1);

			width++;
			// if i is modulo width of world add new line
			if ((i + 1) % pWorld->w == 0)
			{
				height++;
				width = 0;
			}
			// increase pixel pointer of bytes per pixel
			pPixels += pWorld->format->BytesPerPixel;
			continue;
		}

		else if (r == 222 && g == 222 && b == 222)
		{
			// create player
			GPlayer* pAnt2 = new GPlayer
			(SVector2((float)(width * GConfig::s_BlockWidth), (float)(height * GConfig::s_BlockWidth)),
				SVector2((float)GConfig::s_PlayerSrcRectWidth, (float)GConfig::s_PlayerSrcRectHeight));

			// add player to GGM 
			GGM->AddPlayer(pAnt2, 2);


			// initialize player
			pAnt2->Init();
			// set speed
			pAnt2->SetSpeed(GConfig::s_BlockWidth * 5.0f);
			// set collision type to move
			pAnt2->SetColType(MOVE);
			// activate gravity
			pAnt2->ActivateGravity();
			// set Collision-List
			pAnt2->SetCollisionList();
			// set HP to MaxHP
			pAnt2->SetHP(PLAYERMAXHP);
			// tag as Ant 2
			pAnt2->SetTag("Ant2");

			// add player to ctm
			CTM->AddPersistantEntity(pAnt2);

			width++;
			// if i is modulo width of world add new line
			if ((i + 1) % pWorld->w == 0)
			{
				height++;
				width = 0;
			}
			// increase pixel pointer of bytes per pixel
			pPixels += pWorld->format->BytesPerPixel;
			continue;
		}

		// if nothing hit add 0
		else
		{
			width++;
			// if i is modulo width of world add new line
			if ((i + 1) % pWorld->w == 0)
			{
				height++;
				width = 0;
			}
			// increase pixel pointer of bytes per pixel
			pPixels += pWorld->format->BytesPerPixel;
			continue;
		}

		// set source rect of current block
		pEntity->SetSrcRect(SRect(GConfig::s_BlockAtlasWidth, GConfig::s_BlockAtlasHeight, xPosOfTexture, 0));

		// add entity to ctm
		CTM->AddSceneEntity(pEntity);

		// increase width
		width++;

		// increase pixel pointer of bytes per pixel
		pPixels += pWorld->format->BytesPerPixel;

		// if i is modulo width of world add new line
		if ((i + 1) % pWorld->w == 0)
		{
			height++;
			width = 0;
			text.append("\n");
		}

	}
	// return string
	return text;
}
#pragma endregion