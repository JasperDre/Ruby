#include "GamePCH.h"
#include "PokeBall.h"

#include "Entities/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PokeBall::PokeBall(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	m_MyExtrasTileMap = aTileMap;
	myTextureIdentifier = aTexture;

	m_MyFrame = m_MyExtrasTileMap->GetFrameFromExtrasMap("PokeBall_UIScore.png");
	m_MyFrame.myUVOffset = Vector2Float((m_MyFrame.myOrigin.myX / aResourceManager->GetTextureSize(4).x), (m_MyFrame.myOrigin.myY / aResourceManager->GetTextureSize(4).y));
	m_MyFrame.myUVScale = Vector2Float((m_MyFrame.mySize.myX / aResourceManager->GetTextureSize(4).x), (m_MyFrame.mySize.myY / aResourceManager->GetTextureSize(4).y));
}

void PokeBall::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	m_MyFrame.myWorldSpace = myPosition;
	myMesh->Draw(m_MyFrame.myWorldSpace, 0, TILESIZE, 0, camProjection, myTextureIdentifier, m_MyFrame.myUVScale, m_MyFrame.myUVOffset);
}
