#include "GamePCH.h"
#include "Entity.h"
#include "Mesh/Mesh.h"

Entity::Entity(GameCore* pGame, Mesh* pMesh, GLuint atexture)
	: m_pGame(pGame)
	, m_pMesh(pMesh)
	, m_pMyTexture(atexture)
	, m_Position(0, 0)
	, m_Angle(0)
	, m_Radius(10)
	, my_UVOffset(0.0f, 0.0f)
{
}

Entity::~Entity()
{
}

void Entity::Draw(vec2 camPos, vec2 projScale)
{
	if (!m_pMesh)
		return;

	m_pMesh->Draw(m_Position, m_Angle, 1, camPos, projScale, m_pMyTexture, vec2(1.0f, 1.0f), my_UVOffset);
}

bool Entity::IsColliding(Entity* pOtherGameObject)
{
	return false;
}

AStarPathFinder* Entity::GetPathFinder()
{
	if (m_MyPathFinder)
		return m_MyPathFinder;

	return nullptr;
}
