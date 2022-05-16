#include "GamePCH.h"
#include "Canvas.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

Canvas::Canvas(TileMap* aTileMap, ResourceManager* aResourceManager)
	: myIsReversed(false)
{
	myTileMap = aTileMap;
	myResourceManager = aResourceManager;
}

void Canvas::GeneratePalletVertexData(const unsigned short BitMap[MAPSIZE])
{
	//create the masks to find the Tile Type and Variant
	unsigned short TileMask = 15;
	unsigned short VariantMask = 1008;

	for (int i = 0; i < MAPSIZE; i++)
	{
		int j = 0;
		if ((i / NUM_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_COLUMNS - 1) - (i % NUM_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[((i / NUM_COLUMNS) * NUM_COLUMNS) + j] & TileMask;
			unsigned short VariantSelecter = BitMap[((i / NUM_COLUMNS) * NUM_COLUMNS) + j] & VariantMask;

			if (Tile_Type(TileSelecter) != Town_Null_Wall_ && Tile_Type(TileSelecter) != Town_Null_Door_)
			{

				//create a temp TileInfo struct to access the attributes
				TileInfo atile = myTileMap->GetTileFromPalletMap(Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.myVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				Vector2Float aVOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(0).y));
				Vector2Float aUVScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(0).y));

				//set up the position
				Vector2Float aposition = Vector2Float(((((i / NUM_COLUMNS) * NUM_COLUMNS) + j) % NUM_COLUMNS) * TILESIZE, ((((i / NUM_COLUMNS) * NUM_COLUMNS) + j) / NUM_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, Vector2Float(TILESIZE, TILESIZE), aUVScale, aVOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[i] & TileMask;
			unsigned short VariantSelecter = BitMap[i] & VariantMask;

			if (Tile_Type(TileSelecter) != Town_Null_Wall_ && Tile_Type(TileSelecter) != Town_Null_Door_)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = myTileMap->GetTileFromPalletMap(Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.myVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				Vector2Float aUVOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(0).y));
				Vector2Float aUVScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(0).y));

				//set up the position
				Vector2Float aposition = Vector2Float((i % NUM_COLUMNS) * TILESIZE, (i / NUM_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, Vector2Float(TILESIZE, TILESIZE), aUVScale, aUVOffset);
			}
		}
	}
}
void Canvas::GenerateLabVertexData(const unsigned short BitMap[LABSIZE])
{
	//create the masks to find the Tile Type and Variant
	unsigned short TileMask = 15;
	unsigned short VariantMask = 1008;

	for (int i = 0; i < LABSIZE; i++)
	{
		int j = 0;
		if ((i / NUM_LAB_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_LAB_COLUMNS - 1) - (i % NUM_LAB_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j] & TileMask;
			unsigned short VariantSelecter = BitMap[((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j] & VariantMask;

			if (OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullWall_ && OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullDoor_)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = myTileMap->GetTileFromOakLabMap(OakLab_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.myVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				Vector2Float aVOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(1).y));
				Vector2Float aUVScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(1).y));

				//set up the position
				Vector2Float aposition = Vector2Float(((((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j) % NUM_LAB_COLUMNS) * TILESIZE, ((((i / NUM_LAB_COLUMNS) * NUM_LAB_COLUMNS) + j) / NUM_LAB_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, Vector2Float(TILESIZE, TILESIZE), aUVScale, aVOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[i] & TileMask;
			unsigned short VariantSelecter = BitMap[i] & VariantMask;

			if (OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullWall_ && OakLab_Tile_Type(TileSelecter) != Oak_Lab_NullDoor_)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = myTileMap->GetTileFromOakLabMap(OakLab_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.myVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				Vector2Float aUVOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(1).y));
				Vector2Float aUVScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(1).y));

				//set up the position
				Vector2Float aposition = Vector2Float((i % NUM_LAB_COLUMNS) * TILESIZE, (i / NUM_LAB_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, Vector2Float(TILESIZE, TILESIZE), aUVScale, aUVOffset);
			}
		}
	}
}
void Canvas::GenerateForestVertexData(const unsigned short BitMap[FORESTMAPSIZE])
{
	//create the masks to find the Tile Type and Variant
	unsigned short TileMask = 15;
	unsigned short VariantMask = 1008;

	for (int i = 0; i < FORESTMAPSIZE; i++)
	{
		int j = 0;
		if ((i / NUM_FOREST_COLUMNS) % 2 == 1)
		{
			SetIsReverse(true);

			j = (NUM_FOREST_COLUMNS - 1) - (i % NUM_FOREST_COLUMNS);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j] & TileMask;
			unsigned short VariantSelecter = BitMap[((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j] & VariantMask;

			if (Forest_Tile_Type(TileSelecter) != Forest_Null_Wall && Forest_Tile_Type(TileSelecter) != Forest_Null_Door)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = myTileMap->GetTileFromWoodsMap(Forest_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.myVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				Vector2Float aVOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(3).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(3).y));
				Vector2Float aUVScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(3).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(3).y));

				//set up the position
				Vector2Float aposition = Vector2Float(((((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j) % NUM_FOREST_COLUMNS) * TILESIZE, ((((i / NUM_FOREST_COLUMNS) * NUM_FOREST_COLUMNS) + j) / NUM_FOREST_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, Vector2Float(TILESIZE, TILESIZE), aUVScale, aVOffset);
			}
		}
		else
		{
			SetIsReverse(false);

			//Find the index of the Tile Type and Variant at the map index
			unsigned short TileSelecter = BitMap[i] & TileMask;
			unsigned short VariantSelecter = BitMap[i] & VariantMask;

			if (Forest_Tile_Type(TileSelecter) != Forest_Null_Wall && Forest_Tile_Type(TileSelecter) != Forest_Null_Door)
			{
				//create a temp TileInfo struct to access the attributes
				TileInfo atile = myTileMap->GetTileFromWoodsMap(Forest_Tile_Type(TileSelecter));

				//extract the Frame attribute of the correct variant
				Frame aframe = atile.myVariant.at(VariantSelecter / 16 - 1);

				//set the UV's of the tile at the index
				Vector2Float aUVOffset = Vector2Float((aframe.myOrigin.myX / myResourceManager->GetTextureSize(3).x), (aframe.myOrigin.myY / myResourceManager->GetTextureSize(3).y));
				Vector2Float aUVScale = Vector2Float((aframe.mySize.myX / myResourceManager->GetTextureSize(3).x), (aframe.mySize.myY / myResourceManager->GetTextureSize(3).y));

				//set up the position
				Vector2Float aposition = Vector2Float((i % NUM_FOREST_COLUMNS) * TILESIZE, (i / NUM_FOREST_COLUMNS) * TILESIZE);

				AddVert(aposition, 0, Vector2Float(TILESIZE, TILESIZE), aUVScale, aUVOffset);
			}
		}
	}
}
void Canvas::AddVert(Vector2Float objectPos, float objectAngle, Vector2Float objectScale, Vector2Float aUVscale, Vector2Float aUVoffset)
{
	const float radians = objectAngle / 180.0f * Math::pi;

	for (unsigned int i = 0; i < m_BaseTileVerts.size(); i++)
	{
		if (myIsReversed == true)
		{
			Vector2Float finalPos = m_BaseTileVertsReverse.at(i).myPosition;

			finalPos *= objectScale;

			finalPos = Vector2Float(finalPos.myX * cos(radians) - finalPos.myY * sin(radians),
				finalPos.myX * sin(radians) + finalPos.myY * cos(radians));

			finalPos += objectPos;

			Vector2Float UVTemp = m_BaseTileVertsReverse.at(i).myUVCoordinates;

			UVTemp *= aUVscale;

			UVTemp += aUVoffset;

			VertexFormat aVert = VertexFormat(Vector2Float(finalPos), Color(m_BaseTileVertsReverse.at(i).myColor), Vector2Float(UVTemp));

			myCanvasVertices.push_back(aVert);
		}
		else
		{
			Vector2Float finalPos = m_BaseTileVerts.at(i).myPosition;

			finalPos *= objectScale;

			finalPos = Vector2Float(finalPos.myX * cos(radians) - finalPos.myY * sin(radians),
				finalPos.myX * sin(radians) + finalPos.myY * cos(radians));

			finalPos += objectPos;

			Vector2Float UVTemp = m_BaseTileVerts.at(i).myUVCoordinates;

			UVTemp *= aUVscale;

			UVTemp += aUVoffset;

			VertexFormat aVert = VertexFormat(Vector2Float(finalPos), Color(m_BaseTileVerts.at(i).myColor), Vector2Float(UVTemp));

			myCanvasVertices.push_back(aVert);
		}
	}
}

void Canvas::SetIsReverse(bool isreverse)
{
	myIsReversed = isreverse;
}
