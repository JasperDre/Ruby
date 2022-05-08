#include "GamePCH.h"
#include "GameObjects/GameObject.h"

#include "Mesh/Mesh.h"

GameObject::GameObject(GameCore* pGame, Mesh* pMesh, GLuint atexture)
	: m_Position(0, 0)
	, my_UVOffset(0.0f, 0.0f)
	, m_pMyTexture(atexture)
	, m_pGame(pGame)
	, m_pMesh(pMesh)
	, m_MyPathFinder(nullptr)
	, m_Angle(0)
	, m_Radius(10)
	, m_MyMinIndex(0)
	, m_MyMaxIndex(0)
{}

void GameObject::Draw(vec2 camPos, vec2 projScale)
{
	if (m_pMesh != 0)
		m_pMesh->Draw(m_Position, m_Angle, 1, camPos, projScale, m_pMyTexture, vec2(1.0f, 1.0f), my_UVOffset);
}

bool GameObject::IsColliding(GameObject* pOtherGameObject)
{
	return false;
}

void GameObject::OnCollision(GameObject* pOtherGameObject)
{
}