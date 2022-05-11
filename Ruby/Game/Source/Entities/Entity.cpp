#include "GamePCH.h"
#include "Entities/Entity.h"

#include "Mesh/Mesh.h"

Entity::Entity(GameCore* pGame, Mesh* pMesh, unsigned int aTextureIdentifier)
	: m_Position(0, 0)
	, my_UVOffset(0.0f, 0.0f)
	, myTextureIdentifier(aTextureIdentifier)
	, m_pGame(pGame)
	, m_pMesh(pMesh)
	, m_MyPathFinder(nullptr)
	, m_Angle(0)
	, m_Radius(10)
	, m_MyMinIndex(0)
	, m_MyMaxIndex(0)
{}

void Entity::Draw(Vector2Float camPos, Vector2Float projScale)
{
	if (m_pMesh)
		m_pMesh->Draw(m_Position, m_Angle, 1, camPos, projScale, myTextureIdentifier, Vector2Float(1.0f, 1.0f), my_UVOffset);
}

AI_States Entity::GetMyState()
{
	return AI_States::IdleState;
}
