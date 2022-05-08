#include "GamePCH.h"
#include "PokeBall.h"

#include "GameObjects/GameObject.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PokeBall::PokeBall(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_MyResourceManager = aResourceManager;
	m_MyExtrasTileMap = aTileMap;
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;

	m_MyFrame = m_MyExtrasTileMap->GetFrameFromExtrasMap("PokeBall_UIScore.png");
	m_MyFrame.myUVOffset = vec2((m_MyFrame.myOrigin.x / m_MyResourceManager->GetTextureSize(4).x), (m_MyFrame.myOrigin.y / m_MyResourceManager->GetTextureSize(4).y));
	m_MyFrame.myUVScale = vec2((m_MyFrame.mySize.x / m_MyResourceManager->GetTextureSize(4).x), (m_MyFrame.mySize.y / m_MyResourceManager->GetTextureSize(4).y));
}

void PokeBall::Draw(vec2 camPos, vec2 camProjection)
{
	m_MyFrame.myWorldSpace = m_Position;
	m_pMesh->Draw(m_MyFrame.myWorldSpace, 0, TILESIZE, 0, camProjection, m_pMyTexture, m_MyFrame.myUVScale, m_MyFrame.myUVOffset);
}
