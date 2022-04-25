#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "PokeBall.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapExtras.h"
#include "GameplayHelpers/ResourceManager.h"
#include "Mesh/Mesh.h"

#include "Game/Game.h"

PokeBall::PokeBall(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_MyResourceManager = aResourceManager;
	m_MyExtrasTileMap = aTileMap;
	m_pMesh = myMesh;
	m_pMyTexture = aTexture; 

	m_MyFrame = m_MyExtrasTileMap->GetFrameFromExtrasMap("PokeBall_UIScore.png");
	m_MyFrame.uvoffset = vec2((m_MyFrame.origin.x / m_MyResourceManager->GetTextureSize(4).x), (m_MyFrame.origin.y / m_MyResourceManager->GetTextureSize(4).y));
	m_MyFrame.uvscale = vec2((m_MyFrame.size.x / m_MyResourceManager->GetTextureSize(4).x), (m_MyFrame.size.y / m_MyResourceManager->GetTextureSize(4).y));
}

PokeBall::~PokeBall()
{

}

void PokeBall::Update(float deltatime)
{

}

void PokeBall::Draw(vec2 camPos, vec2 camProjection)
{
	m_MyFrame.worldSpace = m_Position;
	m_pMesh->Draw(m_MyFrame.worldSpace, 0, TILESIZE, 0, camProjection, m_pMyTexture, m_MyFrame.uvscale, m_MyFrame.uvoffset);
}
