#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "Entity.h"
#pragma endregion

#pragma region forward decleration
class CMoveEntity;
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// class to manage update, render and delete of all entities
/// </summary>
class CContentManagement : public CEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CContentManagement() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CContentManagement();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	virtual void Update(float _deltaTime) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get all scene entities
	/// </summary>
	/// <returns>list of all scene entities</returns>
	inline list<CEntity*> GetSceneEntities() { return m_pSceneEntities; }

	/// <summary>
	/// add entity to scene entities
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	inline void AddSceneEntity(CEntity* _pEntity) { AddEntity(_pEntity, m_pSceneEntities); }

	/// <summary>
	/// get all persistant entities
	/// </summary>
	/// <returns>list of all persistant entities</returns>
	inline list<CEntity*> GetPersistantEntities() { return m_pPersistantEntities; }

	/// <summary>
	/// add entity to persistant entities
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	inline void AddPersistantEntity(CEntity* _pEntity) { AddEntity(_pEntity, m_pPersistantEntities); }

	/// <summary>
	/// get all ui entities
	/// </summary>
	/// <returns>list of all ui entities</returns>
	inline list<CEntity*> GetUIEntities() { return m_pUIEntities; }

	/// <summary>
	/// add entity to ui entities
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	inline void AddUIEntity(CEntity* _pEntity) { AddEntity(_pEntity, m_pUIEntities); }

	/// <summary>
	/// clean all scene objects
	/// </summary>
	inline void CleanSceneObjects() { CleanEntities(m_pSceneEntities); }

	/// <summary>
	/// clean all persistant objects
	/// </summary>
	inline void CleanPersistantObjects() { CleanEntities(m_pPersistantEntities); }

	/// <summary>
	/// clean all UI objects
	/// </summary>
	inline void CleanUIObjects() { CleanEntities(m_pUIEntities); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// remove entity from game
	/// </summary>
	/// <param name="_pEntities">entity</param>
	void RemoveEntity(CEntity* _pEntities);

	/// <summary>
	/// sort list by layer
	/// </summary>
	/// <param name="_pList">list</param>
	void SortList(list<CEntity*> &_pList);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// time until collision check
	/// </summary>
	float m_collisionTime = 0.0f;

	/// <summary>
	/// current collision check time
	/// </summary>
	float m_currentColTime = 0.0f;
#pragma endregion

#pragma region private variable
	/// <summary>
	/// list with all scene entity references
	/// </summary>
	list<CEntity*> m_pSceneEntities;

	/// <summary>
	/// list with all persistant entity references
	/// </summary>
	list<CEntity*> m_pPersistantEntities;

	/// <summary>
	/// list with all ui entity references
	/// </summary>
	list<CEntity*> m_pUIEntities;

	/// <summary>
	/// list of all move entities
	/// </summary>
	list<CMoveEntity*> m_pMoveEntities;

	/// <summary>
	/// list of all entities to remove next frame
	/// </summary>
	list<CEntity*> m_pRemoveEntities;
#pragma endregion

#pragma region private function
	/// <summary>
	/// add entity to list
	/// </summary>
	/// <param name="_pEntity">entity reference to add</param>
	/// <param name="_pList">list reference to add to</param>
	void AddEntity(CEntity* _pEntity, list<CEntity*> &_pList);

	/// <summary>
	/// clean all entities in list
	/// </summary>
	/// <param name="_list">list</param>
	void CleanEntities(list<CEntity*> &_list);
#pragma endregion
};