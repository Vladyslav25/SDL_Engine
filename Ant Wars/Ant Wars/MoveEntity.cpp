#pragma region project include
#include "MoveEntity.h"
#include "Engine.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Macro.h"
#include "Player.h"
#pragma endregion

#pragma region public override function
CMoveEntity::~CMoveEntity()
{
}

// update every frame
void CMoveEntity::Update(float _deltaTime)
{
	// check gravity movement down
	CheckCollision(_deltaTime, SVector2(0.0f, 1.0f), CPhysic::s_Gravity, m_gravity, true);

	// check collision with collision list
	CheckCollision(_deltaTime, m_movement, m_speed, false, false);

	// update parent
	CTexturedEntity::Update(_deltaTime);
}

// render every frame
void CMoveEntity::Render()
{
	CTexturedEntity::Render();
}
#pragma endregion

#pragma region public function
// fill collision list with all collidable entities near
void CMoveEntity::SetCollisionList()
{
	// if camera too far away return
	if (RENDERER->GetCamera().X > m_position.X + SCREEN_WIDTH ||
		RENDERER->GetCamera().X < m_position.X - SCREEN_WIDTH ||
		RENDERER->GetCamera().Y > m_position.Y + SCREEN_HEIGHT ||
		RENDERER->GetCamera().Y < m_position.Y - SCREEN_HEIGHT)
	{
		return;
	}

	// clear list of collision objects in range
	m_pColEntities.clear();

	// set range check rect
	SRect rangeRect = m_rect;
	rangeRect.x -= (int)COLLISION_RANGE;
	rangeRect.y -= (int)COLLISION_RANGE;
	rangeRect.w += 2 * (int)COLLISION_RANGE;
	rangeRect.h += 2 * (int)COLLISION_RANGE;

	// through all scene objects
	for (CEntity* pEntity : CTM->GetSceneEntities())
	{
		if (!pEntity)
			continue;
		// if current object is textured object min and not self
		if ((CTexturedEntity*)pEntity && pEntity != this)
		{
			// if collision type is none continue
			if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::NONE)
				continue;

			// if current object collides (is in range) with this
			if (CPhysic::RectRectCollision(rangeRect, ((CTexturedEntity*)pEntity)->GetRect()))
				// add current object to collision list
				m_pColEntities.push_front((CTexturedEntity*)pEntity);
		}
	}

	// through all persistant objects
	for (CEntity* pEntity : CTM->GetPersistantEntities())
	{
		if (!pEntity)
			continue;
		// if current object is textured object min and not self
		if ((CTexturedEntity*)pEntity && pEntity != this)
		{
			// if collision type is none continue
			if (((CTexturedEntity*)pEntity)->GetColType() == ECollisionType::NONE)
				continue;

			// if current object collides (is in range) with this
			if (CPhysic::RectRectCollision(rangeRect, ((CTexturedEntity*)pEntity)->GetRect()))
				// add current object to collision list
				m_pColEntities.push_front((CTexturedEntity*)pEntity);
		}
	}
}
#pragma endregion

#pragma region private function
// check collision with collidable objects list
void CMoveEntity::CheckCollision(float _deltaTime, SVector2 _movement, float _speed, bool _checkForGravity, bool _gravityOnly)
{
	// if camera too far away return
	if (RENDERER->GetCamera().X > m_position.X + SCREEN_WIDTH ||
		RENDERER->GetCamera().X < m_position.X - SCREEN_WIDTH ||
		RENDERER->GetCamera().Y > m_position.Y + SCREEN_HEIGHT ||
		RENDERER->GetCamera().Y < m_position.Y - SCREEN_HEIGHT)
	{
		return;
	}

	//// if gravity used but gravity false return
	if (_checkForGravity && !m_gravity)
		return;

	// moveable default true
	bool moveable = true;

	// if gravity used grounded default true
	if (_checkForGravity)
		m_isGrounded = true;

	// reset collision target
	if (_checkForGravity)
		m_pColTarget = nullptr;

	// calculate position to move to
	SVector2 nextPos = {};
	if (_gravityOnly && !_checkForGravity)
		return;
	nextPos = m_position + _movement * _speed * _deltaTime;

	// if gravity used
	if (_checkForGravity)
	{
		// increase fall time
		m_fallTime += _deltaTime;

		// calculate position to move to
		nextPos = m_position + _movement * _speed * m_fallTime * _deltaTime;
	}

	// calculate rect to move to
	SRect rect = m_rect;
	rect.x = (int)nextPos.X;
	rect.y = (int)nextPos.Y;


	// through all collision objects in range
	for (CTexturedEntity* pEntity : m_pColEntities)
	{
		// if current object is textured object min
		if (pEntity != this)
		{
			// get rect from object
			SRect EntityRect = ((CTexturedEntity*)pEntity)->GetRect();
			EntityRect.x = (int)(pEntity->GetPosition().X);
			EntityRect.y = (int)(pEntity->GetPosition().Y);

			// if collision type is none continue
			if (pEntity->GetColType() == ECollisionType::NONE)
				continue;


			// set moveable by checking collision
			moveable = !CPhysic::RectRectCollision(rect, EntityRect);
			// if not moveable cancel collision check
			if (!moveable)
			{
				// set collision target
				m_pColTarget = (CTexturedEntity*)pEntity;
				break;
			}
		}
	}

	// if gravity used and moveable set grounded false
	if (_checkForGravity && moveable)
		m_isGrounded = false;

	// if still moveable set new position
	if (moveable)
		// set next position
		m_position = nextPos;

	// if not moveable and gravity true reset fall time
	else if (_checkForGravity)
		m_fallTime = 0;
}
#pragma endregion