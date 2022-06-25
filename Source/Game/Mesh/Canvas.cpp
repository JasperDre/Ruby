#include "Canvas.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileInfo.h"
#include "GameplayHelpers/TileMap.h"
#include "Math/MathConstants.h"
#include "Mesh/Mesh.h"

namespace CanvasDefinitions
{
	static constexpr unsigned int tileMask = 15;
	static constexpr unsigned int variantMask = 1008;
}

Canvas::Canvas(TileMap* aTileMap, ResourceManager* aResourceManager)
	: myTileMap(aTileMap)
	, myResourceManager(aResourceManager)
	, myIsReversed(false)
{}

void Canvas::GeneratePalletVertexData(const std::vector<unsigned>& aBitMap)
{
	for (unsigned int i = 0; i < aBitMap.size(); i++)
	{
		int j = 0;
		if ((i / NUM_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_COLUMNS - 1) - (i % NUM_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned int tileSelecter = aBitMap[((i / NUM_COLUMNS) * NUM_COLUMNS) + j] & CanvasDefinitions::tileMask;
			const unsigned int variantSelecter = aBitMap[((i / NUM_COLUMNS) * NUM_COLUMNS) + j] & CanvasDefinitions::variantMask;

			if (static_cast<Tile_Type>(tileSelecter) != Town_Null_Wall_ && static_cast<Tile_Type>(tileSelecter) != Town_Null_Door_)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromPalletMap(static_cast<Tile_Type>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame aframe = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(0).y));
				const Vector2Float uvScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(0).y));

				//set up the position
				const Vector2Float pos = Vector2Float(((((i / NUM_COLUMNS) * NUM_COLUMNS) + j) % NUM_COLUMNS) * TILESIZE, ((((i / NUM_COLUMNS) * NUM_COLUMNS) + j) / NUM_COLUMNS) * TILESIZE);

				AddVertex(pos, 0, Vector2Float(TILESIZE, TILESIZE), uvScale, uvOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned short tileSelecter = aBitMap[i] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[i] & CanvasDefinitions::variantMask;

			if (static_cast<Tile_Type>(tileSelecter) != Town_Null_Wall_ && static_cast<Tile_Type>(tileSelecter) != Town_Null_Door_)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromPalletMap(Tile_Type(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(0).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(0).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(0).x), (frame.mySize.myY / myResourceManager->GetTextureSize(0).y));

				//set up the position
				const Vector2Float pos = Vector2Float((i % NUM_COLUMNS) * TILESIZE, (i / NUM_COLUMNS) * TILESIZE);

				AddVertex(pos, 0, Vector2Float(TILESIZE, TILESIZE), uvScale, uvOffset);
			}
		}
	}
}
void Canvas::GenerateLabVertexData(const std::vector<unsigned>& aBitMap)
{
	for (unsigned int i = 0; i < aBitMap.size(); i++)
	{
		int j = 0;
		if ((i / NUM_LAB_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_LAB_COLUMNS - 1) - (i % NUM_LAB_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned short tileSelecter = aBitMap[((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j] & CanvasDefinitions::variantMask;

			if (static_cast<OakLab_Tile_Type>(tileSelecter) != Oak_Lab_NullWall_ && static_cast<OakLab_Tile_Type>(tileSelecter) != Oak_Lab_NullDoor_)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromOakLabMap(static_cast<OakLab_Tile_Type>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(1).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(1).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(1).x), (frame.mySize.myY / myResourceManager->GetTextureSize(1).y));

				//set up the position
				const Vector2Float pos = Vector2Float(((((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j) % NUM_LAB_COLUMNS) * TILESIZE, ((((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j) / NUM_LAB_COLUMNS) * TILESIZE);

				AddVertex(pos, 0, Vector2Float(TILESIZE, TILESIZE), uvScale, uvOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short tileSelecter = aBitMap[i] & CanvasDefinitions::tileMask;
			unsigned short variantSelecter = aBitMap[i] & CanvasDefinitions::variantMask;

			if (static_cast<OakLab_Tile_Type>(tileSelecter) != Oak_Lab_NullWall_ && static_cast<OakLab_Tile_Type>(tileSelecter) != Oak_Lab_NullDoor_)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromOakLabMap(static_cast<OakLab_Tile_Type>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(1).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(1).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(1).x), (frame.mySize.myY / myResourceManager->GetTextureSize(1).y));

				//set up the position
				const Vector2Float pos = Vector2Float((i % NUM_LAB_COLUMNS) * TILESIZE, (i / NUM_LAB_COLUMNS) * TILESIZE);

				AddVertex(pos, 0, Vector2Float(TILESIZE, TILESIZE), uvScale, uvOffset);
			}
		}
	}
}
void Canvas::GenerateForestVertexData(const std::vector<unsigned>& aBitMap)
{
	for (unsigned int i = 0; i < aBitMap.size(); i++)
	{
		int j = 0;
		if ((i / NUM_FOREST_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_FOREST_COLUMNS - 1) - (i % NUM_FOREST_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned short tileSelecter = aBitMap[((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j] & CanvasDefinitions::variantMask;

			if (static_cast<Forest_Tile_Type>(tileSelecter) != Forest_Null_Wall && static_cast<Forest_Tile_Type>(tileSelecter) != Forest_Null_Door)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromWoodsMap(static_cast<Forest_Tile_Type>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(3).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(3).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(3).x), (frame.mySize.myY / myResourceManager->GetTextureSize(3).y));

				//set up the position
				const Vector2Float pos = Vector2Float(((((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j) % NUM_FOREST_COLUMNS) * TILESIZE, ((((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j) / NUM_FOREST_COLUMNS) * TILESIZE);

				AddVertex(pos, 0, Vector2Float(TILESIZE, TILESIZE), uvScale, uvOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			const unsigned short tileSelecter = aBitMap[i] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[i] & CanvasDefinitions::variantMask;
			if (static_cast<Forest_Tile_Type>(tileSelecter) != Forest_Null_Wall && static_cast<Forest_Tile_Type>(tileSelecter) != Forest_Null_Door)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromWoodsMap(static_cast<Forest_Tile_Type>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(3).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(3).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(3).x), (frame.mySize.myY / myResourceManager->GetTextureSize(3).y));

				//set up the position
				const Vector2Float pos = Vector2Float((i % NUM_FOREST_COLUMNS) * TILESIZE, (i / NUM_FOREST_COLUMNS) * TILESIZE);

				AddVertex(pos, 0, Vector2Float(TILESIZE, TILESIZE), uvScale, uvOffset);
			}
		}
	}
}
void Canvas::AddVertex(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float aUVscale, Vector2Float aUVoffset)
{
	const float radians = objectAngle / 180.0f * Math::pi;

	for (unsigned int i = 0; i < myBaseTileVerts.size(); i++)
	{
		if (myIsReversed == true)
		{
			Vector2Float finalPos = myBaseTileVertsReverse.at(i).myPosition;

			finalPos *= objectScale;

			finalPos = Vector2Float(finalPos.myX * cos(radians) - finalPos.myY * sin(radians),
				finalPos.myX * sin(radians) + finalPos.myY * cos(radians));

			finalPos += objectPos;

			Vector2Float UVTemp = myBaseTileVertsReverse.at(i).myUVCoordinates;

			UVTemp *= aUVscale;

			UVTemp += aUVoffset;

			VertexFormat aVert = VertexFormat(Vector2Float(finalPos), Color(myBaseTileVertsReverse.at(i).myColor), Vector2Float(UVTemp));

			myCanvasVertices.push_back(aVert);
		}
		else
		{
			Vector2Float finalPos = myBaseTileVerts.at(i).myPosition;

			finalPos *= objectScale;

			finalPos = Vector2Float(finalPos.myX * cos(radians) - finalPos.myY * sin(radians),
				finalPos.myX * sin(radians) + finalPos.myY * cos(radians));

			finalPos += objectPos;

			Vector2Float UVTemp = myBaseTileVerts.at(i).myUVCoordinates;

			UVTemp *= aUVscale;

			UVTemp += aUVoffset;

			VertexFormat aVert = VertexFormat(Vector2Float(finalPos), Color(myBaseTileVerts.at(i).myColor), Vector2Float(UVTemp));

			myCanvasVertices.push_back(aVert);
		}
	}
}

void Canvas::SetIsReverse(bool anIsreverse)
{
	myIsReversed = anIsreverse;
}
