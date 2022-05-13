#include "GamePCH.h"
#include "OakLabDeskTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabDeskTop::OakLabDeskTop(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	myOakLabDeskTopMap = { 11, 10, 9, 8, 7, 6 };
	myTextureIdentifier = aTexture;
	m_MyTileMap = myTileMap;
	OaklabDeskPosition = Vector2Float(1.0f * TILESIZE, 13.0f * TILESIZE);

	for (unsigned int i = 0; i < myOakLabDeskTopMap.size(); i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_WorkDesk_);
		Frame aframe = atile.MyVariant.at(myOakLabDeskTopMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myWorldSpace = Vector2Float((((i % myOakLabDeskTopMap.size()) * TILESIZE) + OaklabDeskPosition.myX), (((i / myOakLabDeskTopMap.size())* TILESIZE) + OaklabDeskPosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

OakLabDeskTop::~OakLabDeskTop()
{
	m_MyFrames.clear();
}

void OakLabDeskTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < myOakLabDeskTopMap.size(); i++)
		myMesh->Draw(m_MyFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
}
