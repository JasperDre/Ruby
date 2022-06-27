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

void Canvas::GeneratePalletTownVertexData(const std::vector<unsigned>& aBitMap)
{
	for (unsigned int i = 0; i < aBitMap.size(); i++)
	{
		int j = 0;
		if ((i / Columns) % 2 == 1)
		{
			SetIsReverse(true);

			j = (Columns - 1) - (i % Columns);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned int tileSelecter = aBitMap[((i / Columns) * Columns) + j] & CanvasDefinitions::tileMask;
			const unsigned int variantSelecter = aBitMap[((i / Columns) * Columns) + j] & CanvasDefinitions::variantMask;

			if (static_cast<PalletTownTileType>(tileSelecter) != PalletTownTileType::TownNullWall && static_cast<PalletTownTileType>(tileSelecter) != PalletTownTileType::TownNullDoor)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromPalletTownMap(static_cast<PalletTownTileType>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame aframe = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(0).y));
				const Vector2Float uvScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(0).y));

				//set up the position
				const Vector2Float pos = Vector2Float(((((i / Columns) * Columns) + j) % Columns) * TileSize, ((((i / Columns) * Columns) + j) / Columns) * TileSize);

				AddVertex(pos, 0, Vector2Float(TileSize, TileSize), uvScale, uvOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned short tileSelecter = aBitMap[i] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[i] & CanvasDefinitions::variantMask;

			if (static_cast<PalletTownTileType>(tileSelecter) != PalletTownTileType::TownNullWall && static_cast<PalletTownTileType>(tileSelecter) != PalletTownTileType::TownNullDoor)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromPalletTownMap(static_cast<PalletTownTileType>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(0).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(0).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(0).x), (frame.mySize.myY / myResourceManager->GetTextureSize(0).y));

				//set up the position
				const Vector2Float pos = Vector2Float((i % Columns) * TileSize, (i / Columns) * TileSize);

				AddVertex(pos, 0, Vector2Float(TileSize, TileSize), uvScale, uvOffset);
			}
		}
	}
}
void Canvas::GenerateOakLabVertexData(const std::vector<unsigned>& aBitMap)
{
	for (unsigned int i = 0; i < aBitMap.size(); i++)
	{
		int j = 0;
		if ((i / LabColumns) % 2 == 1)
		{
			SetIsReverse(true);

			j = (LabColumns - 1) - (i % LabColumns);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned short tileSelecter = aBitMap[((i / LabColumns) * LabColumns) + j] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[((i / LabColumns) * LabColumns) + j] & CanvasDefinitions::variantMask;

			if (static_cast<OakLabTileType>(tileSelecter) != OakLabTileType::OakLabNullWall && static_cast<OakLabTileType>(tileSelecter) != OakLabTileType::OakLabNullDoor)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromOakLabMap(static_cast<OakLabTileType>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(1).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(1).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(1).x), (frame.mySize.myY / myResourceManager->GetTextureSize(1).y));

				//set up the position
				const Vector2Float pos = Vector2Float(((((i / LabColumns) * LabColumns) + j) % LabColumns) * TileSize, ((((i / LabColumns) * LabColumns) + j) / LabColumns) * TileSize);

				AddVertex(pos, 0, Vector2Float(TileSize, TileSize), uvScale, uvOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short tileSelecter = aBitMap[i] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[i] & CanvasDefinitions::variantMask;

			if (static_cast<OakLabTileType>(tileSelecter) != OakLabTileType::OakLabNullWall && static_cast<OakLabTileType>(tileSelecter) != OakLabTileType::OakLabNullDoor)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromOakLabMap(static_cast<OakLabTileType>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(1).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(1).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(1).x), (frame.mySize.myY / myResourceManager->GetTextureSize(1).y));

				//set up the position
				const Vector2Float pos = Vector2Float((i % LabColumns) * TileSize, (i / LabColumns) * TileSize);

				AddVertex(pos, 0, Vector2Float(TileSize, TileSize), uvScale, uvOffset);
			}
		}
	}
}
void Canvas::GenerateRoute1VertexData(const std::vector<unsigned>& aBitMap)
{
	for (unsigned int i = 0; i < aBitMap.size(); i++)
	{
		int j = 0;
		if ((i / Route1Columns) % 2 == 1)
		{
			SetIsReverse(true);

			j = (Route1Columns - 1) - (i % Route1Columns);

			//Find the index of the Tile Type and Variant at the map index
			const unsigned short tileSelecter = aBitMap[((i / Route1Columns) * Route1Columns) + j] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[((i / Route1Columns) * Route1Columns) + j] & CanvasDefinitions::variantMask;

			if (static_cast<Route1TileType>(tileSelecter) != Route1TileType::NullWall && static_cast<Route1TileType>(tileSelecter) != Route1TileType::NullDoor)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromWoodsMap(static_cast<Route1TileType>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(3).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(3).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(3).x), (frame.mySize.myY / myResourceManager->GetTextureSize(3).y));

				//set up the position
				const Vector2Float pos = Vector2Float(((((i / Route1Columns) * Route1Columns) + j) % Route1Columns) * TileSize, ((((i / Route1Columns) * Route1Columns) + j) / Route1Columns) * TileSize);

				AddVertex(pos, 0, Vector2Float(TileSize, TileSize), uvScale, uvOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			const unsigned short tileSelecter = aBitMap[i] & CanvasDefinitions::tileMask;
			const unsigned short variantSelecter = aBitMap[i] & CanvasDefinitions::variantMask;
			if (static_cast<Route1TileType>(tileSelecter) != Route1TileType::NullWall && static_cast<Route1TileType>(tileSelecter) != Route1TileType::NullDoor)
			{
				//create a temp TileInfo struct to access the attributes
				const TileInfo tileInfo = myTileMap->GetTileFromWoodsMap(static_cast<Route1TileType>(tileSelecter));

				//extract the Frame attribute of the correct variant
				const Frame frame = tileInfo.myVariant.at(variantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				const Vector2Float uvOffset = Vector2Float((frame.myOrigin.myX / myResourceManager->GetTextureSize(3).x), (frame.myOrigin.myY / myResourceManager->GetTextureSize(3).y));
				const Vector2Float uvScale = Vector2Float((frame.mySize.myX / myResourceManager->GetTextureSize(3).x), (frame.mySize.myY / myResourceManager->GetTextureSize(3).y));

				//set up the position
				const Vector2Float pos = Vector2Float((i % Route1Columns) * TileSize, (i / Route1Columns) * TileSize);

				AddVertex(pos, 0, Vector2Float(TileSize, TileSize), uvScale, uvOffset);
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
