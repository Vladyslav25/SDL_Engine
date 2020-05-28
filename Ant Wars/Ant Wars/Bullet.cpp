#pragma region Programmer
// programmed by Frank Sonntag
#pragma endregion

#pragma region project include
#include "Bullet.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Sound.h"
#include "GameManager.h"
#include "Player.h"
#include "Renderer.h"
#pragma endregion

#pragma region public override function

// destructor
GBullet::~GBullet()
{
}

// update every frame
void GBullet::Update(float _deltaTime)
{
	// update parent
	CMoveEntity::Update(_deltaTime);

	// shot timer, counts time after shot
	m_shotTime -= _deltaTime;

	// if collision
	if (m_pColTarget)
	{
		// only creates sounds, if it doesn't exist
		if (m_pExplosion == nullptr)
		{
			// create explosion sound
			m_pExplosion = new CSound("Audio/S_Explosion.ogg");
		}

		// play explosion sound
		m_pExplosion->Play();

		// remove bullet
		CTM->RemoveEntity(this);

		// set shooted on true, so the game manager can go in the next phase
		GGM->SetIsShooted(true);

		// if collision target is ant, add damage
		if (m_pColTarget->GetTag() == "Ant1" || m_pColTarget->GetTag() == "Ant2")
		{
			// adds damage to the ant
			(dynamic_cast<GPlayer*>(m_pColTarget))->AddDamage(100);
			// if ants death after the collision
			if ((dynamic_cast<GPlayer*>(m_pColTarget))->Death())
			{
				// create texture for the gravestone and set in on the middle position of the ant
				m_pGraveStone = new CTexturedEntity(SVector2(m_pColTarget->GetPosition().X + 0.25f * m_pColTarget->GetRect().w, m_pColTarget->GetPosition().Y + 0.5f * m_pColTarget->GetRect().h), // set in on the position of death ant
					SVector2(62.0f, 60.0f),
					"Texture/Character/Player/T_Death.png");
				// add gravestone to ctm
				CTM->AddPersistantEntity(m_pGraveStone);

				// remove death player from his list
				GGM->RemovePlayer((dynamic_cast<GPlayer*>(m_pColTarget)));
			}
		}
	}

	// automatic switch after five (initialized in Bullet.h) seconds, if bullet has no collision
	if (m_shotTime <= 0)
	{
		// set shooted on true, so the game manager can go in the next phase
		GGM->SetIsShooted(true);
		// remove bullet
		CTM->RemoveEntity(this);
	}

}

// render every frame
void GBullet::Render()
{
	CMoveEntity::Render();
}
#pragma endregion