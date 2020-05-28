#pragma region project include
#include "ContentManagement.h"
#include "MoveEntity.h"
#include "Macro.h"
#include "TexturedEntity.h"
#include "Entity.h"
#pragma endregion

#pragma region system include
#include <algorithm>
#pragma endregion

#pragma region destructor
// destructor
CContentManagement::~CContentManagement()
{
	// remove first entity of scene entities until no more left
	while (m_pSceneEntities.size() > 0)
		m_pSceneEntities.pop_front();

	// remove first entity of persistant entities until no more left
	while (m_pPersistantEntities.size() > 0)
		m_pPersistantEntities.pop_front();

	// remove first entity of ui entities until no more left
	while (m_pUIEntities.size() > 0)
		m_pUIEntities.pop_front();
}
#pragma endregion

#pragma region public override function
// update every frame
void CContentManagement::Update(float _deltaTime)
{
	// until no more entities to remove
	while (m_pRemoveEntities.size() > 0)
	{
		// get first entity reference
		CEntity* pEntity = m_pRemoveEntities.front();

		// remove entity from scene list
		m_pSceneEntities.remove(pEntity);

		// remove entity from persistant list
		m_pPersistantEntities.remove(pEntity);

		// remove entity from ui list
		m_pUIEntities.remove(pEntity);

		// if object to remove is move object
		if (dynamic_cast<CMoveEntity*>(pEntity))
		{
			// remove object from move object list
			m_pMoveEntities.remove((CMoveEntity*)pEntity);

			// set collision timer
			m_collisionTime = COLLISION_CHECK_TIME / m_pMoveEntities.size();
		}

		// remove and delete first entity to remove
		m_pRemoveEntities.pop_front();
		delete pEntity;
	}

	// update every scene entity
	for (CEntity* _pEntity : m_pSceneEntities)
		_pEntity->Update(_deltaTime);

	// update every ui entity
	for (CEntity* _pEntity : m_pUIEntities)
		_pEntity->Update(_deltaTime);

	// update every persistant entity
	for (CEntity* _pEntity : m_pPersistantEntities)
		_pEntity->Update(_deltaTime);

	// decrease collision check time
	m_currentColTime -= _deltaTime;

	// if collision check time over 0 return
	if (m_currentColTime > 0 || m_pMoveEntities.size() == 0)
		return;

	// check collision of first move entity in list
	m_pMoveEntities.front()->SetCollisionList();

	// set first element to last
	CMoveEntity* pMoveObj = m_pMoveEntities.front();
	m_pMoveEntities.remove(pMoveObj);
	m_pMoveEntities.push_back(pMoveObj);

	// reset collision timer
	m_currentColTime = m_collisionTime;
}

// render every frame
void CContentManagement::Render()
{
	// order is important for layering
	// first list first rendered

	// render every scene entity
	for (CEntity* _pEntity : m_pSceneEntities)
		_pEntity->Render();

	// render every persistant entity
	for (CEntity* _pEntity : m_pPersistantEntities)
		_pEntity->Render();

	// render every ui entity
	for (CEntity* _pEntity : m_pUIEntities)
		_pEntity->Render();
}
#pragma endregion

#pragma region public function
/// <summary>
/// remove entity from game
/// </summary>
/// <param name="_pObject">entity</param>
void CContentManagement::RemoveEntity(CEntity* _pObject)
{
	// add entity to remove list
	if (std::find(m_pRemoveEntities.begin(), m_pRemoveEntities.end(), _pObject) != m_pRemoveEntities.end()) // by Nils :D
	{

	}
	else
	{
		m_pRemoveEntities.push_back(_pObject);
	}
}

/// <summary>
/// sort list by layer
/// </summary>
/// <param name="_pList">list</param>
void CContentManagement::SortList(list<CEntity*> &_pList)
{

}
#pragma endregion

#pragma region private function
// add entity to list
void CContentManagement::AddEntity(CEntity* _pEntity, list<CEntity*> &_pList)
{
	// add entity to list
	_pList.push_back(_pEntity);

	// if entity is a move entity
	if (dynamic_cast<CMoveEntity*>(_pEntity))
	{
		// add to move entity list
		m_pMoveEntities.push_front((CMoveEntity*)_pEntity);

		// set collision time
		m_collisionTime = COLLISION_CHECK_TIME / m_pMoveEntities.size();
	}

	// sort list
	SortList(_pList);
}

// clean all entities in list
void CContentManagement::CleanEntities(list<CEntity*>& _list)
{
	// add each entity in list to entities to remove
	for (CEntity* pEntity : _list)
		m_pRemoveEntities.push_front(pEntity);
}
#pragma endregion