#pragma region Programmer
// Programmed by Frank Sonntag
// WandWalker by Vladi
#pragma endregion

#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "GameManager.h"
#include "Config.h"
#include "Bullet.h"
#include "MenuScene.h"
#include "MainScene.h"
#include "Animation.h"
#include "Sound.h"
#include "Physic.h"
#include "EGameLoop.h"
#include "Timer.h"
#include "Macro.h"
#include "World.h"
#include "Game.h"
#pragma endregion

#pragma region system include
#include <iostream>
#pragma endregion

#define PI 3.14159265358979323846f

#pragma region public override function
GPlayer::~GPlayer()
{
	// delete animations
	delete m_pIdleAnimTop;
	delete m_pShootAnimTop;
	delete m_pIdleAnimDown;
	delete m_pWalkAnimDown;
	delete m_pShotSound;
	delete m_pJump;
	delete m_pAttack;
	delete m_pDeathSound;
}
// update every frame
void GPlayer::Update(float _deltaTime)
{
#pragma region by Vladi
	// Update the Position of the WW Rects
	SetWallRectsPos();
	// Check for Collison
	CheckForNewGround();
#pragma endregion

	// if esc pressed, quit game
	if (CInput::GetKeyDown(SDL_SCANCODE_ESCAPE))
		GAME->QuitGame();

	// reset movement
	m_movement = SVector2();

# pragma region by Vladi - timeLeft
	// Timer to Jump of the Wall/Roof
	static float timeLeft = 0;
	timeLeft -= _deltaTime;
	if (timeLeft < 0)
	{
		m_skipWallCheck = false;
	}
#pragma endregion

	switch (GGM->GetEStatus())
	{
	case PLAYERSELECTION:

		// update parent
		CMoveEntity::Update(_deltaTime);

		// update animation
		UpdateAnimation(_deltaTime);

		if (m_isControlled && m_pFirstUpdate)
		{
			// if tab is pressed, controll switches between player in a team
			if (CInput::GetKeyDown(SDL_SCANCODE_TAB))
			{
				// if player in team 1
				if (GGM->PlayerinTeam1(this))
					// switch players in team 1
					GGM->SwitchPlayer(GGM->GetTeam1());

				// if player in team 2
				if (!GGM->PlayerinTeam1(this))
					// switch players in team 2
					GGM->SwitchPlayer(GGM->GetTeam2());
			}
		}

		// if player is moved in playerselection phase, go to next phase
		if (m_isControlled && (CInput::GetKey(SDL_SCANCODE_A) || CInput::GetKey(SDL_SCANCODE_D) || CInput::GetKey(SDL_SCANCODE_SPACE)))
		{
			GGM->SetIsMoved(true);
			GGM->SetCurrentPlayer(this);
		}

		break;

	case MOVEPHASE:

		// movement left - key a in move phase
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_A))
		{
			// set movement, mirror and walk animation
			m_movement = -currentGround;
			m_PressingA = true;

			// only animation & sound if ant is not jumping
			if (m_isGrounded)
			{
				// set current animation to walk 
				m_pCurrentAnimTop = m_pIdleAnimTop;
				m_pCurrentAnimDown = m_pWalkAnimDown;
				// update animation
				UpdateAnimation(_deltaTime);

				// play walking sound
				m_pWalking->Play();
			}
		}

		// movement right - key d in move phase
		else if (m_isControlled && CInput::GetKey(SDL_SCANCODE_D))
		{
			// set movement, mirror and walk animation
			m_movement = currentGround;
			m_PressingA = false;
			m_PressingD = true;

			// only animation & sound if ant is not jumping
			if (m_isGrounded)
			{
				// set current animation to walk 
				m_pCurrentAnimTop = m_pIdleAnimTop;
				m_pCurrentAnimDown = m_pWalkAnimDown;
				// update animation
				UpdateAnimation(_deltaTime);

				// play walking sound
				m_pWalking->Play();
			}
		}

		// no input movement
		else
		{
			// set movement to zero
			m_movement.X = 0.0f;
			m_movement.Y = 0.0f;

			// set idle animation
			m_pCurrentAnimTop = m_pIdleAnimTop;
			m_pCurrentAnimDown = m_pIdleAnimDown;
		}

		// if space pressed and grounded jump
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_SPACE) && m_isGrounded) // && GGM->eStatus != SHOOTPHASE)
		{
			//m_movement = -currentGround;
			SetFallTime(-GConfig::s_PlayerJump);

			// play jump sound
			m_pJump->Play();

			// if players jumps, he is not grounded
			m_isGrounded = false;

			if (LeftRectActiv)
			{
				m_movement.X = 10;
				m_movement.Y = 0;
				LeftRectActiv = false;
			}
			else if (RightRectActiv)
			{
				m_movement.X = -10;
				m_movement.Y = 0;
				RightRectActiv = false;
			}
			else if (UpRectActiv)
			{
				m_movement.X = 0;
				m_movement.Y = 10;
				UpRectActiv = false;
			}
			else
			{
				m_movement.X = 0;
				m_movement.Y = -10;
				DownRectActiv = false;
			}
			currentGround = SVector2(1, 0);
			m_skipWallCheck = true;
			timeLeft = 2;

			// activate gravity
			ActivateGravity();
		}

		// if q is pressed in movephase
		if (m_isControlled && m_isGrounded && CInput::GetKey(SDL_SCANCODE_Q))
		{
			// set timer down, so the game manager goes into shooting phase
			GGM->SetTimerDown(true);
		}

		// update animation
		UpdateAnimation(_deltaTime);

		break;

	case SHOOTPHASE:

		// movement left - key a in shoot phase
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_A))
		{
			// set movement, mirror and walk animation
			m_mirror.X = false;
			m_pTextureDown->SetMirror(false);
			m_pTextureTop->SetMirror(false);
		}

		// movement left - key d in shoot phase
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_D))
		{
			// set movement, mirror and walk animation
			m_mirror.X = true;
			m_pTextureDown->SetMirror(true);
			m_pTextureTop->SetMirror(true);
		}

		// adjusting shoot target up
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_W))
		{
			// only allow a specific angle to adjust the shoot

			if (m_pTextureTop->GetMirror() == true && m_pTextureTop->GetAngle() > -90.0f)
				m_pTextureTop->SetAngle(m_pTextureTop->GetAngle() - 1);

			else if (m_pTextureTop->GetMirror() == false && m_pTextureTop->GetAngle() < 90.0f)
			{
				m_pTextureTop->SetAngle(m_pTextureTop->GetAngle() + 1);
			}
		}

		// adjusting shoot target down
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_S))
		{
			// only allow a specific angle to adjust the shoot

			if (m_pTextureTop->GetMirror() == true && m_pTextureTop->GetAngle() < 90.0f)
				m_pTextureTop->SetAngle(m_pTextureTop->GetAngle() + 1);

			else if (m_pTextureTop->GetMirror() == false && m_pTextureTop->GetAngle() > -90.0f)
			{
				m_pTextureTop->SetAngle(m_pTextureTop->GetAngle() - 1);
			}
		}

		// set shootpower by pressing space
		if (m_isControlled && CInput::GetKey(SDL_SCANCODE_SPACE))
		{
			// add shootpower with deltatime while pressed
			shootpower += _deltaTime;
		}

		// if key return spawn bullet and only create one bullet in a round (no multiple shoots possible)
		if ((m_isControlled && CInput::GetKeyDown(SDL_SCANCODE_RETURN) || m_IsThrowingGrenade == true) && (GGM->GetBulletCounter() == GGM->GetRounds()))
		{
			// set current animation to walk 
			m_pCurrentAnimTop = m_pShootAnimTop;
			m_pCurrentAnimDown = m_pIdleAnimDown;
			m_IsThrowingGrenade = true;

			// bullet creation after shoot animation 
			if (m_pCurrentAnimTop->GetAnimationPercentage() >= 98.0f)
			{
				// create bullet
				GBullet* pBullet = new GBullet(SVector2(), SVector2(42, 42), "Texture/Weapons/T_Grenade.png");
				pBullet->SetTag("Bullet");

				// raise bullet counter after creating a bullet
				GGM->SetBulletCounter((GGM->GetBulletCounter()) + 1);

				// spawn left (-1) or right (1) from player
				// if mirror set spawn side left
				if (m_mirror.X)
				{
					spawnSide = 1;
					// set mirror of bullet 
					pBullet->SetMirror(1.0f);
				}
				else
				{
					spawnSide = -1;
					// set mirror of bullet 
					pBullet->SetMirror(0.0f);
				}

				// set values
				pBullet->SetColType(ECollisionType::MOVE);
				pBullet->SetSpeed((float)(GConfig::s_BulletSpeed));

				// if spawnside left
				if (spawnSide == -1)
				{
					sinus = sinf((2 * PI / 360)*(m_pTextureTop->GetAngle() - 90));
					cosinus = cosf((2 * PI / 360) * (m_pTextureTop->GetAngle() + 90));
					pBullet->SetMovement(SVector2(sinus, cosinus));
				}
				else // spawnside right
				{
					sinus = sinf((2 * PI / 360)*(m_pTextureTop->GetAngle() + 90));
					cosinus = cosf((2 * PI / 360) * (m_pTextureTop->GetAngle() - 90));
					pBullet->SetMovement(SVector2(sinus, cosinus));
				}

				// calculate radius for spawn point
				radius = sqrtf(
					((0.5f* m_rect.w)*(0.5f* m_rect.w) +
					(0.5f* m_rect.h)*(0.5f* m_rect.h)
						)) + 0.75f * pBullet->GetRect().w;

				// calculate spawn point
				SVector2 spawnPoint;
				spawnPoint.X = sinus * radius;
				spawnPoint.Y = cosinus * radius;

				if (currentGround == SVector2(0.0f, -1.0f))
				{
					spawnPoint.X *= -1.0f;
					spawnPoint.Y *= -1.0f;

					// set bullet position on middle point of player
					pBullet->SetPosition(SVector2(m_position.X + 0.5f * m_rect.w, m_position.Y + 0.5f * m_rect.h));

					// add position, so that the middle of the spawn point of the bullet is on the radius 
					pBullet->AddPosition(SVector2(spawnPoint.X - pBullet->GetRect().w * 0.5f, spawnPoint.Y - pBullet->GetRect().h * 0.5f));

				}


				if (currentGround == SVector2(1.0f, 0.0f))
				{
					// set bullet position on middle point of player
					pBullet->SetPosition(SVector2(m_position.X + 0.5f * m_rect.w, m_position.Y + 0.5f * m_rect.h));

					// add position, so that the middle of the spawn point of the bullet is on the radius 
					pBullet->AddPosition(SVector2(spawnPoint.X - pBullet->GetRect().w * 0.5f, spawnPoint.Y - pBullet->GetRect().h * 0.5f));
				}

				// multiply the shootpower on the regular bullet movement
				pBullet->SetMovement(pBullet->GetMovement() * shootpower);

				// activate gravity for bullet
				pBullet->ActivateGravity();

				// play shot sound
				m_pShotSound->Play();

				// add bullet to content management
				CTM->AddPersistantEntity(pBullet);

				// reset shootpower after shooting
				shootpower = 1.0f;

				// reset variable for shooting animation
				m_IsThrowingGrenade = false;

				// reset angle of upper texture after shooting to normal angle
				m_pTextureTop->SetAngle(0);
			}
		}

		// no input movement in shoot phase, stops current animation and sets it to idle animation
		else if (m_pShootAnimTop->GetAnimationPercentage() >= 98.0f)
		{
			m_PressingD = false;

			m_movement.X = 0.0f;
			m_movement.Y = 0.0f;

			// set idle animation
			m_pCurrentAnimTop = m_pIdleAnimTop;
			m_pCurrentAnimDown = m_pIdleAnimDown;
		}

		// update animation
		UpdateAnimation(_deltaTime);

		// update parent
		CMoveEntity::Update(_deltaTime);

		break;

	default:

		break;
	}

	// update parent
	CMoveEntity::Update(_deltaTime);

	// update animations
	UpdateAnimation(_deltaTime);

	// set camera position to controlled player
	if (m_isControlled && bulletCounter <= GGM->GetRounds())
		RENDERER->SetCamera(m_position);

}
#pragma endregion

void GPlayer::UpdateAnimation(float _deltaTime)
{
	// update current animation
	m_pCurrentAnimTop->Update(_deltaTime);
	m_pCurrentAnimDown->Update(_deltaTime);

	// set source rect by current animation
	m_pTextureTop->SetSrcRect(SRect(
		(int)m_pCurrentAnimTop->GetSize().X,
		(int)m_pCurrentAnimTop->GetSize().Y,
		(int)m_pCurrentAnimTop->GetCurrentTexturePosition().X,
		(int)m_pCurrentAnimTop->GetCurrentTexturePosition().Y
	));
	m_pTextureDown->SetSrcRect(SRect(
		(int)m_pCurrentAnimDown->GetSize().X,
		(int)m_pCurrentAnimDown->GetSize().Y,
		(int)m_pCurrentAnimDown->GetCurrentTexturePosition().X,
		(int)m_pCurrentAnimDown->GetCurrentTexturePosition().Y
	));
	// set texture to position
	m_pTextureDown->SetPosition(m_position);
	m_pTextureTop->SetPosition(m_position);
}

// render every frame
void GPlayer::Render()
{
	CMoveEntity::Render();
}
#pragma endregion

#pragma region public function
// initialize player
void GPlayer::Init()
{
	// create texture for the bottom part of the ant
	m_pTextureDown = new CTexturedEntity(m_position,
		SVector2((float)(GConfig::s_PlayerSrcRectWidth),(float)(GConfig::s_PlayerSrcRectHeight)),
		"Texture/Character/Player/T_Walk.png");
	// add to ctm
	CTM->AddPersistantEntity(m_pTextureDown);

	// create texture for the upper part of the ant
	if (GGM->PlayerinTeam1(this))
	{
		// in blue for ants in team 1
		m_pTextureTop = new CTexturedEntity(m_position,
			SVector2((float)(GConfig::s_PlayerSrcRectWidth), (float)(GConfig::s_PlayerSrcRectHeight)),
			"Texture/Character/Player/T_Grenade_Blue.png");
	}
	else
	{
		// in red for ants in team 2
		m_pTextureTop = new CTexturedEntity(m_position,
			SVector2((float)(GConfig::s_PlayerSrcRectWidth), (float)(GConfig::s_PlayerSrcRectHeight)),
			"Texture/Character/Player/T_Grenade_Red.png");
	}
	// add to ctm
	CTM->AddPersistantEntity(m_pTextureTop);

	// create idle animation top and down
	m_pIdleAnimTop = new CAnimation(SVector2(0.0f, 0.0f),
		SVector2((float)(GConfig::s_PlayerSrcRectWidth),(float)(GConfig::s_PlayerSrcRectHeight)), 1);

	m_pIdleAnimDown = new CAnimation(SVector2(),
		SVector2((float)(GConfig::s_PlayerSrcRectWidth), (float)(GConfig::s_PlayerSrcRectHeight)), 1);

	// create run animation
	m_pWalkAnimDown = new CAnimation(SVector2(), SVector2((float)(GConfig::s_PlayerSrcRectWidth), (float)(GConfig::s_PlayerSrcRectHeight)), 4);
	m_pWalkAnimDown->SetAnimationTime(0.75f);

	// create shoot animation
	m_pShootAnimTop = new CAnimation(SVector2(), SVector2((float)(GConfig::s_PlayerSrcRectWidth), (float)(GConfig::s_PlayerSrcRectHeight)), 5);
	m_pShootAnimTop->SetAnimationTime(0.75f);

	// set idle to current animation
	m_pCurrentAnimTop = m_pIdleAnimTop;
	m_pCurrentAnimDown = m_pIdleAnimDown;

	// create shot sound
	m_pShotSound = new CSound("Audio/S_Attack.ogg");

	// create walking sound
	m_pWalking = new CSound("Audio/S_Walking.ogg");

	// create jumping sound
	m_pJump = new CSound("Audio/S_Jump.ogg");

	// create death sound
	m_pDeathSound = new CSound("Audio/S_Death.ogg");
}

#pragma endregion

// returns if a player is death
bool GPlayer::Death() {
	if (m_pHP > 0)
	{
		return false; // player alive
	}

	else
	{
		// play death sound
		m_pDeathSound->Play();
		return true; // player dead
	}
}


#pragma region Wandwalker
#pragma region Programmer Vladyslav Sorokin
#pragma endregion
//create the WW REcts
void GPlayer::SetWallRects()
{
	//DownRect
	DownRect = SRect(
		(int)(RectWidth  *0.5f), GConfig::s_BlockHeight,//size
		m_rect.x + (int)(RectWidth*0.25f), m_rect.y + (int)(RectHight + 1.0f) //pos
	);
	//UpRect
	UpRect = SRect(
		(int)(RectWidth * 0.5f), GConfig::s_BlockHeight, //size
		m_rect.x + (int)(RectWidth*0.25f), m_rect.y - 10 //pos
	);
	//LeftRect
	LeftRect = SRect(
		GConfig::s_BlockWidth, (int)(RectHight *0.5f),//size
		m_rect.x - 10, m_rect.y + (int)(RectHight*0.25f) //pos
	);
	//RightRect
	RightRect = SRect(
		GConfig::s_BlockWidth, (int)(RectHight *0.5f),//size
		m_rect.x + (int)(RectWidth + 1.0f), m_rect.y + (int)(RectHight*0.25f) //pos
	);
}

void GPlayer::SetWallRectsPos() // Update the Rect Positions
{
	DownRect.SetPos((float)m_rect.x + RectWidth*0.25f, (float)m_rect.y + RectHight + 1.0f); //DownRect
	UpRect.SetPos((float)m_rect.x + RectWidth*0.25f, (float)m_rect.y - 10); //UpRect
	LeftRect.SetPos((float)m_rect.x - 10, (float)m_rect.y + RectHight*0.25f); //LeftRect
	RightRect.SetPos((float)m_rect.x + RectWidth + 1.0f, (float)m_rect.y + RectHight*0.25f);//RightRect
}

void GPlayer::CheckForNewGround() // Check if WW Rects have Collision
{
	if (m_skipWallCheck)
		return;

	for (CTexturedEntity* entity : CMoveEntity::m_pColEntities)
	{
		if (entity->GetTag() == "Ant1" || entity->GetTag() == "Ant2")
			continue;

		//DownRect
		if (/*!DownRectActiv &&*/ CPhysic::RectRectCollision(DownRect, entity->GetRect()) && GGM->GetEStatus() != SHOOTPHASE)

		{
			currentGround = SVector2(1, 0); //set Currendground
			// set Texture Angle
			m_pTextureTop->SetAngle(0);
			m_pTextureDown->SetAngle(0);
			//set mirror
			if (m_PressingD) {
				m_pTextureTop->SetMirror(true);
				m_pTextureDown->SetMirror(true);
				m_mirror.X = true;
			}
			if (m_PressingA) {
				m_pTextureTop->SetMirror(false);
				m_pTextureDown->SetMirror(false);
				m_mirror.X = false;
			}
			DownRectActiv = true;
			//reset Falltime
			SetFallTime(0);
			break;

		}
		else
		{
			DownRectActiv = false;
		}
		// UpRect
		if (CPhysic::RectRectCollision(UpRect, entity->GetRect()) && GGM->GetEStatus() != SHOOTPHASE)
		{
			currentGround = SVector2(1, 0); // Set Currendground
			// Set Texture Angle
			m_pTextureTop->SetAngle(180);
			m_pTextureDown->SetAngle(180);
			if (m_PressingD) {
				m_pTextureTop->SetMirror(false);
				m_pTextureDown->SetMirror(false);
				m_mirror.X = false;
			}
			if (m_PressingA) {
				m_pTextureTop->SetMirror(true);
				m_pTextureDown->SetMirror(true);
				m_mirror.X = true;
			}
			UpRectActiv = true;
			// Reset Falltime
			SetFallTime(0);
			break;

		}
		else {
			UpRectActiv = false;
		}
		// LeftRect
		if (CPhysic::RectRectCollision(LeftRect, entity->GetRect()) && GGM->GetEStatus() != SHOOTPHASE)

		{
			currentGround = SVector2(0, -1); // Set Currendground
			// Set Angle
			this->m_pTextureTop->SetAngle(90);
			this->m_pTextureDown->SetAngle(90);
			// Set Mirror
			if (m_PressingD) {
				m_pTextureTop->SetMirror(false);
				m_pTextureDown->SetMirror(false);
				m_mirror.X = false;
			}
			if (m_PressingA) {
				m_pTextureTop->SetMirror(true);
				m_pTextureDown->SetMirror(true);
				m_mirror.X = true;
			}
			LeftRectActiv = true;
			// Reset Falltime
			SetFallTime(0);
			break;

		}
		else {
			LeftRectActiv = false;
		}
		// RightRect
		if (CPhysic::RectRectCollision(RightRect, entity->GetRect()) && GGM->GetEStatus() != SHOOTPHASE)
		{
			currentGround = SVector2(0, -1); // Set Currendground
			// Set Angle
			this->m_pTextureTop->SetAngle(270);
			this->m_pTextureDown->SetAngle(270);
			// Set Mirror
			if (m_PressingD) {
				m_pTextureTop->SetMirror(true);
				m_pTextureDown->SetMirror(true);
				m_mirror.X = true;
			}

			if (m_PressingA) {
				m_pTextureTop->SetMirror(false);
				m_pTextureDown->SetMirror(false);
				m_mirror.X = false;
			}
			RightRectActiv = true;
			// Reset Falltime
			SetFallTime(0);
			break;
		}
		else {
			RightRectActiv = false;
		}
	}

	if (CMoveEntity::m_pColEntities.size() == 0)
	{
		DownRectActiv = false;
		UpRectActiv = false;
		LeftRectActiv = false;
		RightRectActiv = false;
	}

	// Stuck the Player at the Wall / Roof
	if (!(DownRectActiv || UpRectActiv || LeftRectActiv || RightRectActiv) && GGM->GetEStatus() != SHOOTPHASE) {
		ActivateGravity();
		m_pTextureTop->SetAngle(0);
		m_pTextureDown->SetAngle(0);
		if (m_PressingD) {
			m_pTextureTop->SetMirror(true);
			m_pTextureDown->SetMirror(true);
		}
		if (m_PressingA) {
			m_pTextureTop->SetMirror(false);
			m_pTextureDown->SetMirror(false);
		}
	}
	else
	{
		DeactivateGravity();
		m_isGrounded = true;
	}
}
#pragma endregion